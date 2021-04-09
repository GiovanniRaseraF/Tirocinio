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

bool SensorParamEvent::checkNotify(float value, float currentTime) {
	bool notify = false;

	// Min
	if (min != PARAM_NOT_SET && value <= min && !wasMinRead) {
		prevValue = value;
		notify = true;
		wasMinRead = true;
	}
	else if (min != PARAM_NOT_SET && wasMinRead && value > min) {
		prevValue = value;
		wasMinRead = false;
	}

	// Max
	if (max != PARAM_NOT_SET && value >= max && !wasMaxRead) {
		prevValue = value;
		notify = true;
		wasMaxRead = true;
	}
	else if (max != PARAM_NOT_SET && wasMaxRead && value < max) {
		wasMaxRead = false;
	}

	// Diff
	if (diff != PARAM_NOT_SET && abs(value - prevValue) >= diff && !wasDiffRead) {
		prevValue = value;
		notify = true;
		wasDiffRead = false;
	}
	else if (diff != PARAM_NOT_SET && abs(value - prevValue) < diff && wasDiffRead) {
		wasDiffRead = false;
	}

	// Time
	if (time != PARAM_NOT_SET &&  abs(currentTime - prevTime) >= time) {
		prevTime = currentTime;
		prevValue = value;
		notify = true;

		wasMinRead = false;
		wasMaxRead = false;
		wasDiffRead = false;
	}

	return notify;
}