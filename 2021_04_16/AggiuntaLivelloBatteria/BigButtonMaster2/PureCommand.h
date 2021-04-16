/*
 Name:		PureCommand.h
 Created:	4/7/2021 3:01:10 PM
 Author:	giovannirasera
*/
#pragma once
#include <Arduino.h>
#include <vector>
#define PARAM_NOT_SET 3.40282347e+38f
typedef std::pair<String, float> param_val;

class PureCommand{
public:
	String primary;
	String sensor;
	std::vector<param_val> params{
		{"min",		PARAM_NOT_SET},
		{"max",		PARAM_NOT_SET},
		{"diff",	PARAM_NOT_SET},
		{"time",	PARAM_NOT_SET}
	};

public:
	PureCommand(void) {}
	~PureCommand(void) {}
	PureCommand(const char* p) : PureCommand(String(p)) {}
	PureCommand(const char* p, const  char* s) : PureCommand(String(p), String(s)) {}
	PureCommand(String p) : primary{ p } { p.trim(); }
	PureCommand(String p, String s) : primary{ p }, sensor{ s }{ p.trim(); s.trim(); }
	PureCommand(String p, String s, std::vector<param_val> pv): 
		primary{ p }, 
		sensor{ s }{
		p.trim(); 
		s.trim();
		for (auto p : pv)
			this->set(p.first, p.second);
	}

public:
	PureCommand addPrimary(const char* p) {
		return addPrimary(String(p));
	}

	PureCommand addPrimary(std::string p) {
		return addPrimary(String(p.c_str()));
	}

	PureCommand addPrimary(String p) {
		primary = p;
		primary.trim();

		return *this;
	}

	PureCommand addSensor(const char* s) {
		return addSensor(String(s));
	}

	PureCommand addSensor(std::string s) {
		return addSensor(String(s.c_str()));
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

	PureCommand set(std::string param, std::string sValue) {
		return set(String(param.c_str()), String(sValue.c_str()));
	}

	float get(String param) const {
		param.trim();

		for (auto p : params)
			if (p.first == param)
				return p.second;

		return PARAM_NOT_SET;
	}

	/// <summary>
	/// Estract all setted params
	/// </summary>
	/// <param name="into">Where to store them</param>
	void get(std::vector<param_val>& into) {
		for (auto p : params)
			if(p.second != PARAM_NOT_SET)
				into.push_back(p);
	}

	String toString(void) const {
		String ret = "command info:\n";

		ret += "- " + primary + "\n";
		ret += "- " + sensor + "\n";
		ret += "- params:\n";
		for (auto p : params) 
			ret += "---- [" + p.first + "]: " + (p.second == PARAM_NOT_SET ? "PARAM_NOT_SET" :  String(p.second)) + "\n";

		return ret;
	}

};

