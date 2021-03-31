#include "ServiceHandler.h"

ServiceHandler::ServiceHandler(BLELocalDevice& B) : started{ false }, BLE{ B }{
}

int ServiceHandler::start() {
	//Always add the logReportService
	logReportService = std::make_pair<const String, BLEService&>("logReport", service.logReportServiceUUID);
	logReportService.second.addCharacteristic(service.logReportMessageCharacteristic);
	BLE.setAdvertisedService(logReportService.second);
	BLE.addService(logReportService.second);
	started = true;
	
	allActivatedServices.push_back(logReportService);

	return 2;
}

bool ServiceHandler::activateService(String& serviceName) {
	if (serviceName == String("location")) {

	}
}

BLEService ServiceHandler::getBLEService(const String& serviceName) {
	for (auto i : allActivatedServices) 
		if (i.first.compareTo(serviceName)) 
			return i.second;

	Serial.print("ServiceHandler: Service not present: ");
	Serial.println(serviceName);
	
	service.logReportMessageCharacteristic.writeValue("SH: NO " + serviceName);

	return {};
}

bool ServiceHandler::isServiceActive(const String& serviceName) {
	for (auto i : allActivatedServices)
		if (i.first.compareTo(serviceName) == 0)
			return true;

	return false;
}

String ServiceHandler::getAllActiveServicesNames() const {
	String ret = "";
	
	for (auto i : allActivatedServices) 
		ret += i.first + "\n";
	
	return ret;
}


