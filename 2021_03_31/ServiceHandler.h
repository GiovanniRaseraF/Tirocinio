/*
 Name:		ServiceHandler.h
 Created:	3/31/2021 11:00:00 AM
 Author:	giovannirasera
*/
#pragma once
#include <ArduinoBLE.h>
#include "Caracteristics.h"
#include <vector>
#include <tuple>

class ServiceHandler
{
private:
	bool started;
	BLELocalDevice& BLE;
	Service service{};

private:


private: // Available Services to add <serviceName, service>
	std::pair<String, BLEService> locationService;
	std::pair<String, BLEService> temperatureService;
	std::pair<String, BLEService> humidityService;

	std::pair<String, BLEService> logReportService;

	//Contains the above services and custom services
	std::vector<std::pair<String, BLEService>> allActivatedServices;

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

	bool activateService(String& serviceName);
	BLEService getBLEService(const char* serviceName) { return getBLEService(String(serviceName)); }
	BLEService getBLEService(const String& serviceName);
	bool isServiceActive(const String& serviceName);
	String getAllActiveServicesNames() const;
};

