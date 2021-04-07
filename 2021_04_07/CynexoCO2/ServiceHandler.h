/*
 Name:		ServiceHandler.h
 Created:	3/31/2021 11:00:00 AM
 Author:	giovannirasera
*/
#pragma once
#include <ArduinoBLE.h>
#include <Wire.h>
#include <Arduino_HTS221.h>
#include <vector>
#include <tuple>
#include <functional>
#include <algorithm>
#include <time.h>
#include "SensorParamEvent.h"
#define TEMPERATURE_OFFSET 5

class ServiceHandler{
private:
	bool started;
	BLELocalDevice& BLE;

public: // Available Services
	// Environmental
	BLEService environmentService{ "181A" };	
	// LogReport
	BLEService messageService{ "19B10000-E8F2-537E-4F6C-D104768A1214" };

public: // Available Characteristics
	// Temperature
	SensorParamEvent temperatureEvent{ 20, 25, 4, 1200000 };
	BLEIntCharacteristic temperatureCharacteristic{
		"2A6E",  
		BLERead | BLENotify
	};
	// Temperature
	SensorParamEvent humidityEvent{ 20, 50, 4, 600000 };
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

public:
	ServiceHandler(BLELocalDevice& B);

	/*
	* Return values:
	*	0 : BLE starting failed
	*	1 : BLE started and logService active
	*	2 : BLE started and logService inactive
	*/
	int start();
	inline bool isStarted() { return started; }

	bool activateService(String serviceName);
	bool isServiceActive(const String& serviceName);
	String getAllActiveServicesNames() const;

	/*
	* Return the temperature:
	*	- it will be offsetted by TEMPERATURE_OFFSET
	* to fix offset use:
	*	- https://www.arduino.cc/en/Guide/NANO33BLESense
	*	- section -> Relative humidity and temperature 
	*				on the Arduino NANO 33 BLE Sense
	*/
	float readTemperature();

	/*
	* Return the humidity:
	*	- TO DO adjust readings
	*/
	float readHumidity();
	
	float readCo2();

	float readNoise();

	bool writeLogReport(String message);

	/*
	* Return the bytes in a string format
	* NOTE: Not all bytes are read in a single call
	*/
	String readCommand();

	/*
	* Return the error message
	*/
	String executeParsedCommand(std::vector<String>& tokens);

	String setNotifyOn(std::vector<String>& tokens, SensorParamEvent& sensorEvent);

	String update();

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
};

