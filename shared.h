#pragma once

enum eEngineState
{
	ENGINE_STATE_OFF,
	ENGINE_STATE_STARTING,
	ENGINE_STATE_RUN,
	ENGINE_STATE_STOPPING
};

enum eGearboxAction
{
	GEARBOX_ACT_0,
	GEARBOX_ACT_IDLE,
	GEARBOX_ACT_PRE_SHIFTUP,
	GEARBOX_ACT_SHIFTUP,
	GEARBOX_ACT_PRE_SHIFTDOWN,
	GEARBOX_ACT_SHIFTDOWN
};

enum eGears
{
	REVERSE,
	NEUTRAL,
	_1ST,
	_2ND,
	_3RD,
	_4TH,
	_5TH,
	_6TH,
	_7TH,
	_8TH
};

enum eGameStatus
{
	MENU_OPENED				= 1,
	CUTSCENE_INTERIOR		= 3,
	CAR_SELECT				= 7,
	MAP_OPENED				= 131,
	PLAYER_DRIVING			= 191,
	CUTSCENE_INOUT_GARAGE	= 229
};

struct matrix3x4_t
{
	float value[16];
};

struct Vector3
{
	float x;
	float y;
	float z;
};

struct Vector4
{
	float x;
	float y;
	float z;
	float a;
};
