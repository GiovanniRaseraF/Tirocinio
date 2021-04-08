#pragma once
#include <vector>
#include <Stream.h>

/// <summary>
/// Possible Principles:
///		- get {SENSOR};
///			- SENSOR
///			- temperature
///			- humidity
///			- co2
///			- noise
/// 
///		- set-notify {SENSOR} ({PARAMA} {VAL}, {PARAMA} {VAL},);  
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
///			- co2
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
	String command{ "" };

public:
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

	void clearCommand() {
		command = "";
	}

	String getSensor(String& com) {
		String ret = "";

		com.trim();
		for (String SENSOR : SENSORS) {
			if (com.indexOf(SENSOR) >= 0)
				return SENSOR;
		}

		return ret;
	}

	std::vector<String> getParamsVals(String& com) {
		std::vector<String> ret{};

		com.trim();
		if (!(com[0] == '(' && ')' == com[com.length() - 1]))
			return {"No ( ) found"};
		com = com.substring(1, com.length() - 1);

		// Estracting
		while (com.indexOf(',') > 0) {
			com.trim();
			int posComa = com.indexOf(',');
			String param_val = com.substring(0, posComa);

			int posSpace = param_val.indexOf(' ');
			if (posSpace > 0) {
				String param = com.substring(0, posSpace);
				ret.push_back(param);

				String val = com.substring(posSpace, posComa);
				ret.push_back(val);
			}
	
			com = com.substring(posComa + 1);
		}

		return ret;
	}

	std::vector<String> tokenize(String& com) {
		std::vector<String> ret{};
		int posSpace = 0;
		com.toLowerCase();

		if (com.indexOf(';') >= 0) {
			command += com.substring(0, com.indexOf(';'));
			//return { command };
		}else{
			command += com;
			return {};
		}

		// Getting command
		command.trim();
		posSpace = command.indexOf(' ');
		if (posSpace < 0) {
			clearCommand();
			return {"No command"};
		}

		String get_set = command.substring(0, posSpace);
		get_set.trim();
		command = command.substring(posSpace);
		command.trim();

		// GET
		if (get_set == "get") {
			ret.push_back(get_set);

			// Getting sensor
			String sensor = getSensor(command);
			if (sensor == "") {
				clearCommand();
				return { "No sensor found" };
			}
			ret.push_back(sensor);
		}
		// SET-NOTIFY
		else if (get_set == "set-notify") {
			ret.push_back(get_set);

			// Getting sensor
			String sensor = getSensor(command);
			if (sensor == "") {
				clearCommand();
				return { "No sensor found" };
			}
			ret.push_back(sensor);

			// Getting params
			command.trim();
			posSpace = command.indexOf(' ');
			if (posSpace < 0) {
				clearCommand();
				return { "No params" };
			}
			command = command.substring(posSpace);
			command.trim();

			std::vector<String> params_vals = getParamsVals(command);
			if (params_vals.empty()) {
				clearCommand();
				return { command,  "Wrong paramas or values" };
			}

			// Adding params and val
			for (String p_v : params_vals) {
				ret.push_back(p_v);
			}

		}
		else {
			clearCommand();
			return {"Wrong Commmand"};
		}

		clearCommand();
		return ret;
	}
};

/*
* get temperature;
* 
set-notify co2 ( min 14,);
set-notify co2 ( min 14,);
set-notify co2 ( min 14, max 15, diff 12, time 432,);
set-notify humidity ( min 14, max 15, diff 12, time 432.);
set-notify temperature ( min 14, time 432,);
set-notify noise ( min 14, max 15, diff 12, time 432,);


set-notify temperature ( min 20, max 25, diff 12, time 6000,);
set-notify temperature ( min 20, max 25, diff 12, time 60000,);
get temperature;
get humidity;
get co2;
get noise;

Set-notify hello (min 14);

*/
