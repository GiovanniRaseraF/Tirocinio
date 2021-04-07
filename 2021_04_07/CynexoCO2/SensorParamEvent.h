#pragma once
#include <ArduinoBLE.h>
#include <Wire.h>
#include <Arduino_HTS221.h>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <time.h>

class SensorParamEvent {
public:
	float prevValue = 0;
	
	bool wasMinRead = false;
	float min = 0;

	bool wasMaxRead = false;
	float max = 0;

	bool wasDiffRead = false;
	float diff = 0;

	unsigned long prevTime = 0;
	unsigned long time = 100;

public:
	SensorParamEvent() {};
	SensorParamEvent(float min, float max, float diff, float time);

	void setNotify(float min, float max, float diff, float time);
	bool checkNotify(float value, unsigned long currentTime);
};