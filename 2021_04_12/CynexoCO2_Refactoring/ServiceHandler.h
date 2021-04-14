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
#include "SCD30.h"
#include "PureCommand.h"
#include "Tokenizer.h"
#include "SensorParamEvent.h"
#define TEMPERATURE_OFFSET 5
#define MIN_DELAY_LOWPOWER 2000
#define RED 22                    
#define BLUE 24            
#define GREEN 23 

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

  float readCo2();
  bool notifyCo2(float co2);
  /* Danger levels            Color               Min     Max
  // Good                     Green               Below   1000
  // Attention                Yellow              1000    1400
  // More attention           Yellow blinking     1400    2000
  // Bad                      Red    blinking     2000    Above*/
  void blinkDangerLed(float co2);
  
	bool writeLogReport(String& message);
	
	
	/*float readNoise();
	bool notifyNoise(float noise);*/

public:
	String line{};
	String readLineFromBLE(void);
	String executePureCommand(PureCommand& command);
	String update(String& line, unsigned long& currentTime, unsigned long& pastTime);

private:
	BLELocalDevice& BLE;
  float resultHTC[3];

public:
	int delayTimeMillis = 2000; //10 seconds

public: // Available Services
	// Environmental
	BLEService environmentService{ "181A" };
	// LogReport
	BLEService messageService{ "19B10000-E8F2-537E-4F6C-D104768A1214" };

public: // Available Characteristics
	// Temperature
	PureCommand temperatureDefault{ String("Temperature"), String("default"), {
		{"min", 20},
		{"max", 25},
		{"diff", 2},
		{"time", 2000}
	} };
	SensorParamEvent temperatureEvent{ temperatureDefault };
	BLEIntCharacteristic temperatureCharacteristic{
		"2A6E",
		BLERead | BLENotify 
	};
	// Humidity
	PureCommand humidityDefault{ String("Humidity"), String("default"), {
		{"min", 25},
		{"max", 40},
		{"diff", 15},
		{"time", 2000}
	} };
	SensorParamEvent humidityEvent{ humidityDefault };
	BLEIntCharacteristic humidityCharacteristic{
		"2A6F",
		BLERead | BLENotify
	};
  // CO2
  PureCommand co2Default{ String("Co2"), String("default"), {
    {"min", 25},
    {"max", 40},
    {"time", 2000}
  } };
  SensorParamEvent co2Event{ co2Default };
  BLEIntCharacteristic co2Characteristic{
    "936b6a25-e503-4f7c-9349-bcc76c22b8c3",
    BLERead | BLENotify
  };
	// LogReport
	BLEStringCharacteristic logReportMessageCharacteristic{
		"19B10001-E8F2-537E-4F6C-D104768A1214",
		BLERead,
		50
	};
	// Command
	BLEStringCharacteristic commandMessageCharacteristic{
		"19B10002-E8F2-537E-4F6C-D104768A1214",
		BLEWrite | BLERead,
		200
	};


};
