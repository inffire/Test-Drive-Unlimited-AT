#include <io.h>
#include <time.h>
#include <iostream>
#include <Windows.h>

#include "tduapi.h"

using namespace std;

#define WORLD_PTR			0x1293880
#define RPM_MULTIPLER		9.5492964

/*
	BYTE bNotGamePaused = *(BYTE*)(TestDriveUnlimited.exe+103EDD4);
*/

BYTE*		bGameStatus;
CWorld*		world = (CWorld*)WORLD_PTR;
HMODULE		hDllSelf = 0;
HMODULE		hBase = 0;
clock_t		t = clock();

void CreateConsole()
{
	if (!AllocConsole())
		MessageBox(NULL, "The console window was not created", NULL, MB_ICONEXCLAMATION);
	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
}

float getTorqueOnRPM(CEngineInfo* engineInfo, float fTargetRPM)
{
	if (!engineInfo->m_pAccelerationPlotBegin || !engineInfo->m_pDecellerationPlotBegin ||
		!engineInfo->m_iAccelerationArrayLength || !engineInfo->m_iDecellerationArrayLength)
		return 0;

	if (fTargetRPM <= engineInfo->m_fRpmIdle)
		return *(float*)(engineInfo->m_pAccelerationPlotBegin + 0 * 8 + 4);

	if (fTargetRPM >= engineInfo->m_fRedlineLimitHigh)
	{
		int idx = engineInfo->m_iAccelerationArrayLength - 1;
		return *(float*)(engineInfo->m_pAccelerationPlotBegin + idx * 8 + 4);
	}

	for (int i = 0; i < engineInfo->m_iAccelerationArrayLength - 1; i++)
	{
		float fRPM[2] = { 0 };
		float fTorque[2] = { 0 };

		fRPM[0] = *(float*)(engineInfo->m_pAccelerationPlotBegin + i * 8);
		fRPM[1] = *(float*)(engineInfo->m_pAccelerationPlotBegin + (i + 1) * 8);

		fTorque[0] = *(float*)(engineInfo->m_pAccelerationPlotBegin + i * 8 + 4);
		fTorque[1] = *(float*)(engineInfo->m_pAccelerationPlotBegin + (i + 1) * 8 + 4);

		if (fRPM[0] <= fTargetRPM && fRPM[1] > fTargetRPM)
		{
			float dr = (fTargetRPM - fRPM[0]) / (fRPM[1] - fRPM[0]);
			float fTorqueInterpolated = dr * (fTorque[1] - fTorque[0]) + fTorque[0];
			return fTorqueInterpolated;
		}
	}
	return 1;
}

float getRPMOnHP(CEngineInfo* engineInfo, float fTargetHP)
{
	float fRPM = engineInfo->m_fRpmIdle;
	float fRPMLimit = 0.5f * (engineInfo->m_fRedlineLimitHigh - engineInfo->m_fRedlineLimitLow) + engineInfo->m_fRedlineLimitLow - 1.0f; // полечить
	float balance = 0.2f;
	// fRPMLimit = (1.0f - balance) * engineInfo->m_fRedlineLimitLow + balance * engineInfo->m_fRedlineLimitHigh;// -15.0f;
	fRPMLimit = engineInfo->m_fRedlineLimitHigh - 50.0f;
#ifdef _DEBUG
	printf("%.2f %.2f %.2f\n", engineInfo->m_fRedlineLimitHigh, engineInfo->m_fRedlineLimitLow, fRPMLimit);
#endif
	float step = 10.0f;
	float fCurrentHP = 0.0f;

	while (fCurrentHP <= fTargetHP)
	{
		if (fRPM >= fRPMLimit)
		{
			fRPM = fRPMLimit;
			break;
		}

		float torqueOnRPM = getTorqueOnRPM(engineInfo, fRPM);
		fCurrentHP = torqueOnRPM * fRPM / 735.5f;
		fRPM += step;
	}
	return fRPM;
}

DWORD __stdcall Main(void* plParam)
{
	while (1)
	{
		if (GetAsyncKeyState(VK_END))
			FreeLibraryAndExitThread(hDllSelf, 0);
	#ifdef _DEBUG
		system("cls");
	#endif
		if (world->m_pVehiclePoolBegin)
		{
			if (*bGameStatus != eGameStatus::PLAYER_DRIVING)
			{
			#ifdef _DEBUG
				cout << "paused";
			#endif
				continue;
			}

			CVehicle* vehicle = world->m_pVehiclePoolBegin;
			float fOptimalRPM = 0;

			if (!vehicle->m_pEngineInfo)
				continue;

			if (!vehicle->m_pEngineInfo->m_pAccelerationPlotBegin || !vehicle->m_pEngineInfo->m_pDecellerationPlotBegin)
				continue;

			if (vehicle->m_pEngineInfo->m_pAccelerationPlotBegin)
			{
				float fHpMaximum = -7700.0f;
				float fHpMaximumRPM = 0.0f;
				float fHpMinimum = +7700.0f;
				float fHpMinimumRPM = 0.0f;

				for (int i = 0; i < vehicle->m_pEngineInfo->m_iAccelerationArrayLength; i++)
				{
					float fRPM		= *(float*)(vehicle->m_pEngineInfo->m_pAccelerationPlotBegin + i * 8);
					float fTorque	= *(float*)(vehicle->m_pEngineInfo->m_pAccelerationPlotBegin + i * 8 + 4);
					float fHp		= fTorque * fRPM / 735.5f;

					if (fHp > fHpMaximum)
					{
						fHpMaximum = fHp;
						fHpMaximumRPM = fRPM;
					}

					if (fHp < fHpMinimum)
					{
						fHpMinimum = fHp;
						fHpMinimumRPM = fRPM;
					}
				}

				float fNonLinearAcceleration = vehicle->N0000449F_acc * vehicle->N0000449F_acc;
				fOptimalRPM = getRPMOnHP(vehicle->m_pEngineInfo, fNonLinearAcceleration * fHpMaximum);

			#ifdef _DEBUG
				printf("%.2f NLINEAR_ACC %.2f BRAKE\n", fNonLinearAcceleration, vehicle->N0000449E_brake);
				printf("Req. %.2f hp @ %.2f rad/s (c. %.2f rad/s)\n", fNonLinearAcceleration * fHpMaximum, fOptimalRPM, vehicle->m_pEngineInfo->m_fRpm);
			#endif
			}

			float* fRPMFromWheel = new float[vehicle->m_iGearRatiosArraySize];
			memset(fRPMFromWheel, NULL, vehicle->m_iGearRatiosArraySize * 4);

			if (vehicle->m_pGearRatios)
			{
				float fSlickWheelSpeed_radps = 0.5f * (vehicle->m_pWheelInfo->m_fNativeWheelSpeed_RL + vehicle->m_pWheelInfo->m_fNativeWheelSpeed_RR);
				float fUnslickSpeedOnWheel_radps = 0.5f * (vehicle->m_pWheelInfo->m_fWheelLinearSpeedOnGround_RL + vehicle->m_pWheelInfo->m_fWheelLinearSpeedOnGround_RR)
					/ vehicle->m_pWheelInfo->m_fWheelRadius;

			#ifdef _DEBUG
				printf("Wheels native %.2f rad/s ground %.2f rad/s n/g %.2f\n", fSlickWheelSpeed_radps, fUnslickSpeedOnWheel_radps, fSlickWheelSpeed_radps / fUnslickSpeedOnWheel_radps);
			#endif
				// для колес
				int iGuessedGear = 2;
				float fRPMDelta = 0.0f;

				for (int i = 0; i < vehicle->m_iGearRatiosArraySize; i++)
				{
					float fGearRatio = *(float*)(vehicle->m_pGearRatios + i * 4);
					fRPMFromWheel[i] = fUnslickSpeedOnWheel_radps * fGearRatio * vehicle->m_fFinalRatio;
					fRPMDelta = fRPMFromWheel[i] - fOptimalRPM;
					if (fRPMFromWheel[i] - fOptimalRPM > 0.0f)
					{
					#ifdef _DEBUG
						printf("%d %.2f %.2f delta %3.2f passed\n", i, fGearRatio, fRPMFromWheel[i], fRPMDelta);
					#endif
						iGuessedGear = i+1;
						if (iGuessedGear > vehicle->m_iGearRatiosArraySize-2)
							iGuessedGear = vehicle->m_iGearRatiosArraySize-1;
					}
					else
					{
					#ifdef _DEBUG
						printf("%d %.2f %.2f delta %3.2f\n", i, fGearRatio, fRPMFromWheel[i], fRPMDelta);
					#endif
					}
				}

				if (vehicle->m_iGearboxActionId == eGearboxAction::GEARBOX_ACT_IDLE)
				{
				#ifdef _DEBUG
					printf("go %d gear, current %d\n", iGuessedGear, vehicle->m_iCurrentGear);
				#endif
					if (iGuessedGear > vehicle->m_iCurrentGear )
					{
					#ifdef _DEBUG
						printf("SHIFTUP +%d\n", iGuessedGear - vehicle->m_iCurrentGear);
					#endif
						vehicle->m_iGearboxGearsToSwitch = iGuessedGear - vehicle->m_iCurrentGear;
						vehicle->m_iGearboxActionId = eGearboxAction::GEARBOX_ACT_PRE_SHIFTUP;
					}
					else if (iGuessedGear < vehicle->m_iCurrentGear && fRPMDelta < -100.0f)
					{
					#ifdef _DEBUG
						printf("SHIFTDOWN %d\n", iGuessedGear - vehicle->m_iCurrentGear);
					#endif
						vehicle->m_iGearboxGearsToSwitch = iGuessedGear - vehicle->m_iCurrentGear;
						vehicle->m_iGearboxActionId = eGearboxAction::GEARBOX_ACT_PRE_SHIFTDOWN;
					}
				}
			}
			delete fRPMFromWheel;
		}
		Sleep(200);
	}
	return 0;
}


int __stdcall DllMain(HINSTANCE hInstance, DWORD reason, void* lpReserved)
{
	switch (reason)
	{
	case DLL_PROCESS_ATTACH:
	#ifdef _DEBUG
		CreateConsole();
	#endif
		hDllSelf = hInstance;
		hBase = GetModuleHandle("TestDriveUnlimited.exe");

		if (hBase)
		{
			std::cout << "TestDriveUnlimited.exe " << hex << hBase << "\nCWorld* " << world << endl;
			bGameStatus = (BYTE*)(hBase + 0xBA4714 / sizeof(DWORD));

			CreateThread(0, 0, &Main, 0, 0, 0);

		}
		break;
	case DLL_PROCESS_DETACH:
	#ifdef _DEBUG
		FreeConsole();
	#endif
		break;
	}
	return TRUE;
}