#include "ServiceHandler.h"

ServiceHandler::ServiceHandler(BLELocalDevice& B) : started{ false }, BLE{ B }{}

int ServiceHandler::start() {
	messageService.addCharacteristic(logReportMessageCharacteristic);
	messageService.addCharacteristic(commandMessageCharacteristic);
	BLE.setAdvertisedService(messageService);
	BLE.addService(messageService);

	environmentService.addCharacteristic(temperatureCharacteristic);
	environmentService.addCharacteristic(humidityCharacteristic);
	BLE.setAdvertisedService(environmentService);
	BLE.addService(environmentService);

	started = true;
	
	return 2;
}

float ServiceHandler::readTemperature() {
	int cicles = 10;
	float temperature = 0;

	for (int i = 0; i < cicles; i++) {
		temperature += HTS.readTemperature();
		
		delay(200);
	}
	temperature = (temperature / cicles) - TEMPERATURE_OFFSET;
	
	// need to be scaled * 100
	temperatureCharacteristic.writeValueLE(temperature * 100);
	
	return temperature;
}

float ServiceHandler::readHumidity() {
	int cicles = 10;
	float humidity = 0;

	for (int i = 0; i < cicles; i++) {
		humidity += HTS.readHumidity();

		delay(200);
	}
	humidity = (humidity / cicles);

	// need to be scaled * 100
	humidityCharacteristic.writeValueLE(humidity * 100);
	
	return humidity;
}

bool ServiceHandler::writeLogReport(String message) {
	//Serial.println("ServiceHandler: Writing...");
	
	logReportMessageCharacteristic.writeValue(message);
	//Serial.print("ServiceHandler: Wrote ->");
	//Serial.println(message);
	
	return true;
}

String ServiceHandler::readCommand() {
	String ret = "";

	if (commandMessageCharacteristic.written())
		ret = commandMessageCharacteristic.value();
	
	return ret;
}





































bool ServiceHandler::isServiceActive(const String& serviceName) {
	/*String serviceNameTrim = serviceName;
	serviceNameTrim.trim();

	for (auto i : allActivatedServices)
		if (i.name.compareTo(serviceNameTrim) == 0)
			return true;*/

	return false;
}

String ServiceHandler::getAllActiveServicesNames() const {
	String ret = "";
	/*
	for (auto i : allActivatedServices) 
		ret += i.name + "\n";
	*/
	return ret;
}

bool ServiceHandler::activateService(String serviceName) {
	serviceName.trim();
	return false;
}

