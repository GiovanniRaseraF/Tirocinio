#pragma once
#include <ArduinoBLE.h>
#include <vector>

class Service : public BLEService{
public:
	String name;

	Service(const char* n, const char* uuid) : name{ n }, BLEService(uuid) {}
	
	Service() {};
	~Service() {};

	void start() {}
	void stop() {}

	virtual int readInt() {
		return 0;
	}

	virtual float readFloat() {
		return 0;
	}

};

// LogReport
class LogReportService : public Service {
public:
	BLEStringCharacteristic logReportMessageCharacteristic{
		"19B10001-E8F2-537E-4F6C-D104768A1214",
		BLERead,
		50 
	};

	LogReportService() : Service("logReport", "19B10000-E8F2-537E-4F6C-D104768A1214") {
		addCharacteristic(logReportMessageCharacteristic);
	}

	~LogReportService() {
	}

	int readInt() override {
		return 1;
	}
};

// Temperature
class TemperatureService : public Service {
public:
	BLEIntCharacteristic temperatureValueCharacteristic{ 
		"2A6E",  // Standard Temperature characteristic
		BLERead | BLENotify
	};

	TemperatureService() : Service("temperature", "20B10000-E8F2-537E-4F6C-D104768A1214") {
		addCharacteristic(temperatureValueCharacteristic);
	}

	~TemperatureService(){}

	// Information read
	float readFloat() {
		//float temperature = HTS.readTemperature();
		//temperatureValueCharacteristic.writeValue(11.54);

		return -1;
	}

	int readInt() override {
		return 0;
	}
};