/*
 Name:		CynexoCO2_Refactoring.ino
 Created:	4/7/2021 3:01:10 PM
 Author:	giovannirasera
*/
#include <ArduinoBLE.h>
#include <Arduino.h>
#include <Wire.h>
#include "PureCommand.h"
#include "Tokenizer.h"

void setup() {
	Serial.begin(9600);
	while (!Serial);
}

void loop() {
	String line("get temperature;");

	PureCommand command = Tokenizer::createCommand(line);
	Serial.println(command.toString());
	//Serial.println(" fdsfsda");
	//while (true);
}
