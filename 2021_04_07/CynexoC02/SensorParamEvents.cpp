#include "SensorParamEvent.h"

SensorParamEvent::SensorParamEvent(float min, float max, float diff, float time) {
	this->min = min;
	this->max = max;
	this->diff = diff;
	this->time = abs(round(time));

	wasMinRead = false;
	wasMaxRead = false;
	wasDiffRead = false;
}

void SensorParamEvent::setNotify(float min, float max, float diff, float time) {
	this->min = min;
	this->max = max;
	this->diff = diff;
	this->time = abs(round(time));

	wasMinRead = false;
	wasMaxRead = false;
	wasDiffRead = false;
}

bool SensorParamEvent::checkNotify(float value, unsigned long currentTime) {
	bool notify = false;

	// Min
	if (value <= min && !wasMinRead) {
		notify = true;
		wasMinRead = true;
	}
	else if (wasMinRead && value > min) {
		wasMinRead = false;
	}

	// Max
	if (value >= max && !wasMaxRead) {
		notify = true;
		wasMaxRead = true;
	}
	else if (wasMaxRead && value < max) {
		wasMaxRead = false;
	}

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