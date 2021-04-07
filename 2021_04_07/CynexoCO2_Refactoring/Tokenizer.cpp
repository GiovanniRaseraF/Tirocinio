#include "Tokenizer.h"


PureCommand Tokenizer::createCommand(String& line) {
	PureCommand retCommand{"Creating Command", "No Sensor"};
	std::string primary, sensor;
	
	line.trim();
	if (!doesLineEnds(line)) {
		retCommand.addPrimary("Line not ending with ;");
		return retCommand;
	}
	line = line.substring(0, line.indexOf(';'));
	std::stringstream ss{ line.c_str() };

	// Primary && Sensor
	ss >> primary;
	retCommand.addPrimary(primary.c_str());

	ss >> sensor;
	retCommand.addSensor(sensor.c_str());
	
	return retCommand;
}