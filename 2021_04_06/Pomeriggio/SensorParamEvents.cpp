#include "SensorParamEvents.h"

SensorParamEvents::SensorParamEvents(float min, float max, float diff, float time) {
	this->min = min;
	this->max = max;
	this->diff = diff;
	this->time = abs(round(time));

	wasMinRead = false;
	wasMaxRead = false;
	wasDiffRead = false;
}

void SensorParamEvents::setNotify(float min, float max, float diff, float time) {
	this->min = min;
	this->max = max;
	this->diff = diff;
	this->time = abs(round(time));

	wasMinRead = false;
	wasMaxRead = false;
	wasDiffRead = false;
}

bool SensorParamEvents::checkNotify(float value, unsigned long currentTime) {
	bool notify = false;

	// Time
	if (abs(currentTime - prevTime) >= time) {
		prevTime = currentTime;
		notify = true;

		wasMinRead = false;
		wasMaxRead = false;
		wasDiffRead = false;
	}


	return notify;
}