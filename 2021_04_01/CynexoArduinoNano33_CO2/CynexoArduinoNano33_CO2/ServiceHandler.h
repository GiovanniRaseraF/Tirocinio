/*
 Name:		ServiceHandler.h
 Created:	3/31/2021 11:00:00 AM
 Author:	giovannirasera
*/
#pragma once
#include <ArduinoBLE.h>
#include <Wire.h>
#include <Arduino_HTS221.h>
#include "Service.h"
#include <vector>
#include <tuple>

class ServiceHandler
{
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
	BLEIntCharacteristic temperatureCharacteristic{
		"2A6E",  
		BLERead | BLENotify
	};
	// LogReport
	BLEStringCharacteristic logReportMessageCharacteristic{
		"19B10001-E8F2-537E-4F6C-D104768A1214",
		BLERead,
		50
	};
	// Command
	BLEStringCharacteristic commandMessageCharacheristic{
		"19B10002-E8F2-537E-4F6C-D104768A1214",
		BLEWrite,
		50
	};

public:
	ServiceHandler(BLELocalDevice& B);

	/*
	* return values:
	*	0 : BLE starting failed
	*	1 : BLE started and logService active
	*	2 : BLE started and logService inactive
	*/
	int start();
	inline bool isStarted() { return started; }

	bool activateService(String serviceName);
	bool isServiceActive(const String& serviceName);
	String getAllActiveServicesNames() const;

	float readTemperature();
	bool writeLogReport(String message);
	String readCommand();
};

