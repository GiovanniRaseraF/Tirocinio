/*
 Name:		ServiceHandler.h
 Created:	4/8/2021 11:00:00 AM
 Author:	giovannirasera
*/
#pragma once
#include <ArduinoBLE.h>
#include <Arduino.h>
#include <Wire.h>
#include <Arduino_HTS221.h>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <time.h>
#include "PureCommand.h"
#include "Tokenizer.h"
#define TEMPERATURE_OFFSET 5
#define MIN_DELAY_LOWPOWER 2000

class ServiceHandler{
public:
	ServiceHandler(BLELocalDevice& B);
	bool start(void);

public:	//Utility
	/*
	* Return the temperature:
	*	- it will be offsetted by TEMPERATURE_OFFSET
	* to fix offset use:
	*	- https://www.arduino.cc/en/Guide/NANO33BLESense
	*	- section -> Relative humidity and temperature
	*				on the Arduino NANO 33 BLE Sense
	*/
	float readTemperature(void);
	bool notifyTemperature(float temperature);

	/*
	* Return the humidity:
	*	- TO DO adjust readings
	*/
	float readHumidity(void);
	bool notifyHumidity(float humidity);
	
	bool writeLogReport(String& message);
	
	/*float readCO2();
	bool notifyCO2(float co2);
	float readNoise();
	bool notifyNoise(float noise);*/

public:
	String line{};
	String readLineFromBLE(void);
	String executePureCommand(PureCommand& command);
	String update(String& line, unsigned long& currentTime, unsigned long& pastTime);

private:
	BLELocalDevice& BLE;

public:
	int delayTimeMillis = 10000; //10 seconds

public: // Available Services
	// Environmental
	BLEService environmentService{ "181A" };
	// LogReport
	BLEService messageService{ "19B10000-E8F2-537E-4F6C-D104768A1214" };

public: // Available Characteristics
	// Temperature
	//SensorParamEvent temperatureEvent{ 20, 25, 4, 1200000 };
	BLEIntCharacteristic temperatureCharacteristic{
		"2A6E",
		BLERead | BLENotify 
	};
	// Temperature
	//SensorParamEvent humidityEvent{ 20, 50, 4, 600000 };
	BLEIntCharacteristic humidityCharacteristic{
		"2A6F",
		BLERead | BLENotify
	};

	// LogReport
	BLEStringCharacteristic logReportMessageCharacteristic{
		"19B10001-E8F2-537E-4F6C-D104768A1214",
		BLERead,
		50
	};
	// Command NOT WORKING
	BLEStringCharacteristic commandMessageCharacteristic{
		"19B10002-E8F2-537E-4F6C-D104768A1214",
		BLEWrite | BLERead,
		200
	};


};

