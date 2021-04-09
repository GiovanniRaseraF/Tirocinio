#pragma once
#include <ArduinoBLE.h>
#include <Wire.h>
#include <Arduino_HTS221.h>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <time.h>
#include "PureCommand.h"

class SensorParamEvent {
public:
	float prevValue = 0;
	
	bool wasMinRead = false;
	float min = PARAM_NOT_SET;

	bool wasMaxRead = false;
	float max = PARAM_NOT_SET;

	bool wasDiffRead = false;
	float diff = PARAM_NOT_SET;

	float prevTime = 0;
	float time = PARAM_NOT_SET;

public:
	SensorParamEvent() {};
	SensorParamEvent(PureCommand& command);

	/// <summary>
	/// This function is like initializing the object
	/// Set all params to new values
	/// </summary>
	void setNewNotify(PureCommand& command);

	/// <summary>
	/// Update only the specified params
	/// and the setted params in the command
	/// </summary>
	void setNotify(PureCommand& command);
	bool checkNotify(float value, float currentTime);
};