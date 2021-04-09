#include "SensorParamEvent.h"

SensorParamEvent::SensorParamEvent(PureCommand& command) {
	min = command.get("min");
	max = command.get("max");
	diff = command.get("diff");
	time = command.get("time");

	wasMinRead = false;
	wasMaxRead = false;
	wasDiffRead = false;
}

void SensorParamEvent::setNewNotify(PureCommand& command) {
	min = command.get("min");
	max = command.get("max");
	diff = command.get("diff");
	time = command.get("time");

	wasMinRead = false;
	wasMaxRead = false;
	wasDiffRead = false;
}

void SensorParamEvent::setNotify(PureCommand& command) {
	float min = command.get("min");
	float max = command.get("max");
	float diff = command.get("diff");
	float time = command.get("time");

	this->min = (min == PARAM_NOT_SET? this->min : min);
	this->max = (max == PARAM_NOT_SET? this->max : max);
	this->diff = (diff == PARAM_NOT_SET? this->diff : diff);
	this->time = (time == PARAM_NOT_SET? this->time : time);

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