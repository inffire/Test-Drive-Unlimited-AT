// Generated using ReClass 2016

#pragma once
#include "shared.h"
#include <Windows.h>

// Generated using ReClass 2016

/*
  VehicleInfo[0] <0x1219090> size 0x3A20, count 20
  CWorld <0x1293880>
  CVehicle size 0x43B0

  rpm = rpm * 9.5492964;
  hp = .text:00825272;
*/


class CWorld;
class CVehicle;
class CEngineInfo;
class CGearRatios;
class CWheelInfo;
class StaticVehicleInfo;
class VehicleInfo;
class CTorquePlotPoing;
class CAccelerationPlot;
class CTransmissionInfo;

class CWorld
{
public:
	char pad_0x0000[0x2B8]; //0x0000
	__int32 m_iPoolSize; //0x02B8 
	char pad_0x02BC[0x4]; //0x02BC
	CVehicle* m_pPlayerVehicle; //0x02C0 
	CVehicle* m_pVehiclePoolBegin; //0x02C4 
	CVehicle* m_pVehiclePoolEnd; //0x02C8 

}; //Size=0x02CC

class CVehicle
{
public:
	char pad_0x0000[0x738]; //0x0000
	Vector4 N00004286; //0x0738 
	char pad_0x0748[0x28]; //0x0748
	matrix3x4_t N00004278; //0x0770 
	matrix3x4_t N00004268; //0x07B0 
	matrix3x4_t N00004258; //0x07F0 
	matrix3x4_t N00004648; //0x0830 
	matrix3x4_t N00004638; //0x0870 
	char pad_0x08B0[0x50]; //0x08B0
	matrix3x4_t N00004614; //0x0900 
	char pad_0x0940[0x498]; //0x0940
	float m_fSpeed; //0x0DD8 
	char pad_0x0DDC[0x28]; //0x0DDC
	float N000044D3_acc; //0x0E04 
	float N000044D2_brake; //0x0E08 
	float N000044D1_handbrake; //0x0E0C 
	float N000044D0_steering; //0x0E10 
	char pad_0x0E14[0xA]; //0x0E14
	unsigned char m_bButtonShiftUp; //0x0E1E 
	unsigned char m_bButtonShiftDown; //0x0E1F 
	char pad_0x0E20[0xB4]; //0x0E20
	float N0000449F_acc; //0x0ED4 
	float N0000449E_brake; //0x0ED8 
	float N0000449D_handbrake; //0x0EDC 
	float N0000449C_steering; //0x0EE0 
	char pad_0x0EE4[0x320C]; //0x0EE4
	__int32 m_bIsBike; //0x40F0 
	__int32 m_iWheelCount; //0x40F4 
	char pad_0x40F8[0xC]; //0x40F8
	__int32 m_iEntityType_NPC_1_player_10; //0x4104 
	char pad_0x4108[0x40]; //0x4108
	float m_fCx_coeff; //0x4148 
	char pad_0x414C[0x50]; //0x414C
	__int32 m_bIsCar; //0x419C 
	char pad_0x41A0[0x14]; //0x41A0
	__int32 m_iAllowGearboxAction; //0x41B4 
	char pad_0x41B8[0x1C]; //0x41B8
	float m_fWheelSlideCoeff; //0x41D4 
	float m_fShiftUpTime; //0x41D8 
	float m_fShifDownTime; //0x41DC 
	char pad_0x41E0[0x10]; //0x41E0
	float m_fRedline_LowHigh_Balance; //0x41F0 
	float m_fRedline_LowHigh_Balance_1_Gear; //0x41F4 
	char pad_0x41F8[0x1C]; //0x41F8
	float m_fSpeed_ms; //0x4214 
	char pad_0x4218[0x8]; //0x4218
	Vector3 m_vSpeed1; //0x4220 
	char pad_0x422C[0xC]; //0x422C
	float m_fSpeed_ms_2; //0x4238 
	char pad_0x423C[0x4]; //0x423C
	__int32 m_bIsAnyWheelLostContact; //0x4240 
	char pad_0x4244[0x14]; //0x4244
	__int32 m_iGearboxActionId; //0x4258 
	__int32 m_iGearboxGearsToSwitch; //0x425C 
	char pad_0x4260[0xC]; //0x4260
	float m_fZeroTenValue; //0x426C 
	char pad_0x4270[0x10]; //0x4270
	float m_fSteeringAxis; //0x4280 
	float m_fBrakeAxis; //0x4284 
	float m_fHandbrakeAxis; //0x4288 
	float m_fResistanceForceMultipler; //0x428C 
	float m_fSideForce; //0x4290 
	float m_fAirResistanceForce1; //0x4294 
	float m_fAirResistanceForce2; //0x4298 
	float m_fSideForceConst; //0x429C 
	Vector4 m_vSpeed2; //0x42A0 
	Vector4 m_vPosition; //0x42B0 
	__int32 m_iCurrentGear; //0x42C0 
	char pad_0x42C4[0xC]; //0x42C4
	CEngineInfo* m_pEngineInfo; //0x42D0 
	char pad_0x42D4[0x4]; //0x42D4
	__int32 m_iGearRatiosArraySize; //0x42D8 
	DWORD m_pGearRatios; //0x42DC 
	float m_fFinalRatio; //0x42E0 
	char pad_0x42E4[0x8]; //0x42E4
	__int32 m_iCurrentGear2; //0x42EC 
	char pad_0x42F0[0x8]; //0x42F0
	float m_fRpmAppliedToWheels; //0x42F8 
	char pad_0x42FC[0x4]; //0x42FC
	float m_fRpmAppliedToWheelsDelta1; //0x4300 
	float m_fRpmAppliedToWheels_x100; //0x4304 
	float m_fRpmAppliedToWheelsDelta2; //0x4308 
	float m_fRpmAppliedToWheelsDelta3; //0x430C 
	char pad_0x4310[0x8]; //0x4310
	float m_f_1_MinusClutchIfEngine_ON; //0x4318 
	float m_f_1_MinusClutchIfEngine_ON_and_OFF; //0x431C 
	char pad_0x4320[0x30]; //0x4320
	CWheelInfo* m_pWheelInfo; //0x4350 
	CTransmissionInfo* m_pTransmissionInfo; //0x4354 
	char pad_0x4358[0x58]; //0x4358

}; //Size=0x43B0

class CEngineInfo
{
public:
	float m_fShiftDownRPM; //0x0000 
	float m_fRedlineLimitHigh; //0x0004 
	float m_fRpmIdle; //0x0008 
	float m_fRedlineLimitLow; //0x000C 
	char pad_0x0010[0x18]; //0x0010
	float m_fStartupTime; //0x0028 
	char pad_0x002C[0xC]; //0x002C
	float m_fEngineOverheatCooldown; //0x0038 
	float m_fFinalTorqueMultipler; //0x003C 
	char pad_0x0040[0x44]; //0x0040
	__int32 m_iDecellerationArrayLength; //0x0084 
	__int32 m_iAccelerationArrayLength; //0x0088 
	DWORD m_pDecellerationPlotBegin; //0x008C 
	DWORD m_pAccelerationPlotBegin; //0x0090 
	__int32 m_iEngineState; //0x0094 
	char pad_0x0098[0x4]; //0x0098
	float m_fRpmAcceleration; //0x009C 
	char pad_0x00A0[0x4]; //0x00A0
	float m_fRpm; //0x00A4 
	char pad_0x00A8[0x8]; //0x00A8
	float m_fEngineStateDuring; //0x00B0 
	char pad_0x00B4[0x4]; //0x00B4
	float m_fTurboOmega; //0x00B8 
	float m_fTurboAccel; //0x00BC 
	float m_fTurboPressure; //0x00C0 
	char pad_0x00C4[0x8]; //0x00C4
	__int32 m_iStartupButton; //0x00CC 
	float m_fTorque; //0x00D0 
	float m_fTorqueLastFrame; //0x00D4 
	char pad_0x00D8[0x7D0]; //0x00D8

}; //Size=0x08A8

class CGearRatios
{
public:
	float reverse; //0x0000 
	float neutral; //0x0004 
	float _1st; //0x0008 
	float _2nd; //0x000C 
	float _3rd; //0x0010 
	float _4th; //0x0014 
	float _5th; //0x0018 
	float _6th; //0x001C 
	float _7th; //0x0020 
	float _8th; //0x0024 

}; //Size=0x0028

class CWheelInfo
{
public:
	char pad_0x0000[0x1F0]; //0x0000
	float m_fClutch; //0x01F0 
	char pad_0x01F4[0x11C]; //0x01F4
	float m_fWheelLinearSpeedOnGround_FL; //0x0310 
	char pad_0x0314[0xD4]; //0x0314
	float m_fNativeWheelSpeed_FL; //0x03E8 
	char pad_0x03EC[0x374]; //0x03EC
	float m_fWheelLinearSpeedOnGround_FR; //0x0760 
	char pad_0x0764[0xD4]; //0x0764
	float m_fNativeWheelSpeed_FR; //0x0838 
	char pad_0x083C[0x288]; //0x083C
	float m_fWheelRadius; //0x0AC4 
	char pad_0x0AC8[0xE8]; //0x0AC8
	float m_fWheelLinearSpeedOnGround_RL; //0x0BB0 
	char pad_0x0BB4[0xD4]; //0x0BB4
	float m_fNativeWheelSpeed_RL; //0x0C88 
	char pad_0x0C8C[0x374]; //0x0C8C
	float m_fWheelLinearSpeedOnGround_RR; //0x1000 
	char pad_0x1004[0xD4]; //0x1004
	float m_fNativeWheelSpeed_RR; //0x10D8 

}; //Size=0x10DC

class StaticVehicleInfo
{
public:
	char pad_0x0000[0xE0]; //0x0000
	float timer; //0x00E0 
	char pad_0x00E4[0x1BC]; //0x00E4
	float rpm1; //0x02A0 
	float torque1; //0x02A4 
	int backLights; //0x02A8 
	int frontLights; //0x02AA 
	char pad_0x02AC[0x50]; //0x02AC
	float distance_travelled; //0x02FC 
	char pad_0x0300[0x18]; //0x0300
	float steer1; //0x0318 
	float steer2; //0x031C 
	char pad_0x0320[0x4]; //0x0320
	float acceleration_axis; //0x0324 
	float brake_axis; //0x0328 
	float rpm2; //0x032C 
	float hp; //0x0330 
	float torque2; //0x0334 
	float speed_kmph; //0x0338 
	char pad_0x033C[0x36E4]; //0x033C

}; //Size=0x3A20

class VehicleInfo
{
public:
	StaticVehicleInfo data[20]; //0x0000 

}; //Size=0x48A80

class CTorquePlotPoing
{
public:
	float rpm; //0x0000 
	float torque; //0x0004 

}; //Size=0x0008

class CAccelerationPlot
{
public:
	CTorquePlotPoing N00003716[1]; //0x0000 
	char pad_0x0008[0x400]; //0x0008

}; //Size=0x0408

class CTransmissionInfo
{
public:
	char pad_0x0000[0xAC]; //0x0000
	float m_fTorqueFrontRearBalance; //0x00AC 

}; //Size=0x00B0

