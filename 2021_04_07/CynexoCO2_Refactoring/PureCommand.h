/*
 Name:		PureCommand.h
 Created:	4/7/2021 3:01:10 PM
 Author:	giovannirasera
*/
#pragma once
#include <Arduino.h>
#include <vector>
#define PARAM_NOT_SET 3.40282347e+38f

class PureCommand{
public:
	String primary;
	String sensor;
	std::vector<std::pair<String, float>> params{
		{"min",		PARAM_NOT_SET},
		{"max",		PARAM_NOT_SET},
		{"diff",	PARAM_NOT_SET},
		{"time",	PARAM_NOT_SET}
	};

public:
	PureCommand() {}
	~PureCommand() {}
	PureCommand(const char* p) : PureCommand(String(p)) {}
	PureCommand(const char* p, const  char* s) : PureCommand(String(p), String(s)) {}
	PureCommand(String p) : primary{ p } { p.trim(); }
	PureCommand(String p, String s) : primary{ p }, sensor{ s }{ p.trim(); s.trim(); }

public:
	PureCommand addPrimary(String p) {
		primary = p;
		primary.trim();

		return *this;
	}

	PureCommand addSensor(String s) {
		sensor = s;
		sensor.trim();

		return *this;
	}

	/// <summary>
	/// Try to set the value of a specific parameter
	/// if none is present it will not be notified
	/// </summary>
	/// <returns>the object</returns>
	PureCommand set(String param, float value) {
		param.trim();

		for (auto& p : params)
			if (p.first == param)
				p.second = value;

		return *this;
	}

	PureCommand set(String param, String sValue) {
		float value = 0;

		value = sValue.toFloat();
		
		return set(param, value);
	}

	float get(String param) const {
		param.trim();

		for (auto p : params)
			if (p.first == param)
				return p.second;

		return PARAM_NOT_SET;
	}

	String toString() const {
		String ret = "command info:\n";

		ret += "\t" + primary + "\n";
		ret += "\t" + sensor + "\n";
		ret += "\tparams:\n";
		for (auto p : params) 
			ret += "\t\t[" + p.first + "]: " + String(p.second) + "\n";


		return ret;
	}

};

