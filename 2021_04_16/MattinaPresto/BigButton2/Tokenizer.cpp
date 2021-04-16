#include "Tokenizer.h"

bool Tokenizer::doesLineEnds(String& line) {
	if (line.indexOf(';') >= 0)
		return true;

	return false;
}

PureCommand Tokenizer::createCommand(String line) {
	PureCommand retCommand{"Creating Command", "No Sensor"};
	std::string primary, sensor;
	std::string param{};
	float val = 0;
	if (line == "")
		return {"Blank","Blank"};
	
	line.toLowerCase();
	line.replace('(', ' ');
	line.replace(')', ' ');
	line.replace(',', ' ');
	line.replace('\n', ' ');
	line.trim();
	if (!doesLineEnds(line)) {
		retCommand.addPrimary("Line not ending with ;");
		return retCommand;
	}
	line = line.substring(0, line.indexOf(';'));
	std::stringstream ss{ line.c_str() };

	// Primary && Sensor
	if (ss >> primary)
		retCommand.addPrimary(primary);

	if (ss >> sensor)
		retCommand.addSensor(sensor);

	while (ss >> param >> val) {
		retCommand.set(param.c_str(), val);
	}
	
	return retCommand;
}