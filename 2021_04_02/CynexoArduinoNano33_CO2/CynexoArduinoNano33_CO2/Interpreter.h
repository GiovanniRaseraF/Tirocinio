#pragma once
#include <vector>
#include <Stream.h>

/// <summary>
/// Possible Principles:
///		- get {SENSOR}
///			- SENSOR
///			- temperature
///			- humidity
///			- co2
///			- noise
/// 
///		- set-notify {SENSOR} ({PARAMA} {VAL}, {PARAMA} {VAL},..)  
///			- SENSOR:
///				- PARAM VAL
///			- temperature
///				- min	val
///				- max	val
///				- diff	val
///				- time	val
///			- humidity
///				- min 	val
///				- max	val
///				- diff	val
///				- time	val
///			- c02
///				- min	val
/// 			- max	val
///				- diff	val
///				- time	val
///			- noise
///				- min	val
/// 			- max	val
///				- diff	val
///				- time	val
/// </summary>
class Interpreter {
private:
	std::vector<String> SENSORS{
		"temperature",
		"humidity",
		"co2",
		"noise"
	};

	std::vector<String> PARAMS{
		"min",
		"max",
		"diff",
		"time"
	};

public:
	Interpreter() {};
	~Interpreter() {};

	String getSensor(String& command) {
		String ret = "";

		command.trim();
		for (String SENSOR : SENSORS) {
			if (command.indexOf(SENSOR) >= 0)
				return SENSOR;
		}

		return ret;
	}

	std::vector<String> getParamasVals(String& command) {
		std::vector<String> ret{};

		command.trim();
		if (!(command[0] == '(' && ')' == command[command.length() - 1]))
			return {};
		command = command.substring(1, command.length() - 1);

		// TO DO
		while (command.indexOf(',') > 0) {
			int posComa = command.indexOf(',');


		}

		return ret;
	}

	std::vector<String> tokenize(String& command) {
		std::vector<String> ret{};
		int posSpace = 0;
		
		// Getting command
		command.trim();
		posSpace = command.indexOf(' ');
		if (posSpace < 0)
			return {"No command"};

		String get_set = command.substring(0, posSpace);
		get_set.trim();
		command = command.substring(posSpace);
		command.trim();

		if (get_set == "get") {
			ret.push_back(get_set);

			// Getting sensor
			String sensor = getSensor(command);
			if (sensor == "")
				return { "No sensor found" };
			
			ret.push_back(sensor);
		}
		else if (get_set == "set-notify") {
			ret.push_back(get_set);

			// Getting sensor
			String sensor = getSensor(command);
			if (sensor == "")
				return { "No sensor found" };

			// Getting params
			command.trim();
			posSpace = command.indexOf(' ');
			if (posSpace < 0)
				return { "No params" };
			command = command.substring(posSpace);
			command.trim();

			std::vector<String> params_vals = getParamasVals(command);
			if (params_vals.empty())
				return { "Wrong paramas or values" };



		}
		else {
			return {"Wrong Commmand"};
		}

		return ret;
	}
};
