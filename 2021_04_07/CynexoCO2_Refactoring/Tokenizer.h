/*
 Name:		Tokenizer.h
 Created:	4/7/2021 3:01:10 PM
 Author:	giovannirasera
*/
#pragma once
#include <Arduino.h>
#include "PureCommand.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>

class Tokenizer{
private:
	static String line;

private:
	/*static String getSensor(String& line);
	static std::vector<String> getParamsVals(String& line);
	static std::vector<String> tokenize(String& line);*/

	static bool doesLineEnds(String& line) { return true; }

public:
	static PureCommand createCommand(String& line);

};

