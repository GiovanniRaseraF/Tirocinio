#include "ServiceHandler.h"

ServiceHandler::ServiceHandler(BLELocalDevice& B) : started{ false }, BLE{ B }{}

int ServiceHandler::start() {
	messageService.addCharacteristic(logReportMessageCharacteristic);
	messageService.addCharacteristic(commandMessageCharacheristic);
	BLE.setAdvertisedService(messageService);
	BLE.addService(messageService);

	environmentService.addCharacteristic(temperatureCharacteristic);
	BLE.setAdvertisedService(environmentService);
	BLE.addService(environmentService);

	started = true;
	
	return 2;
}

float ServiceHandler::readTemperature() {
	int cicles = 1;
	float temperature = 0;

	for (int i = 0; i < cicles; i++) {
		temperature += HTS.readTemperature();
		delay(10);
	}
	temperature /= cicles;
	
	// need to be scaled * 100
	temperatureCharacteristic.writeValueLE(temperature * 100);
	
	return temperature;
}

bool ServiceHandler::writeLogReport(String message) {
	logReportMessageCharacteristic.writeValue(message);

	return true;
}

String ServiceHandler::readCommand() {
	String ret = commandMessageCharacheristic.value();

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

