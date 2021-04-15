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
public:
	/*static String getSensor(String& line);
	static std::vector<String> getParamsVals(String& line);
	static std::vector<String> tokenize(String& line);*/

	static bool doesLineEnds(String& line);

public:
	static PureCommand createCommand(String line);

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

