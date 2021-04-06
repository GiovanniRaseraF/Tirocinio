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

float ServiceHandler::readCo2() {
	int cicles = 10;
	float co2 = 0;

	return co2;
}

float ServiceHandler::readNoise() {
	int cicles = 10;
	float noise = 0;

	return noise;
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
	
	if (commandMessageCharacteristic.written()) {
		ret = commandMessageCharacteristic.value();
	}
	
	return ret;
}

String ServiceHandler::executeParsedCommand(std::vector<String>& tokens) {
	String error = "";
	String command = "";
	String sensor = "";

	if (tokens.empty())
		return "No token in tokens";

	command = tokens[0];
	sensor = tokens[1];

	// Execution
	if (command == "get") {
		if (sensor == "temperature")
			readTemperature();
		else if (sensor == "humidity")
			readHumidity();
		else if (sensor == "co2")
			readCo2();
		else if (sensor == "noise")
			readNoise();
		else
			return (String("Cannot find sensor: ") + sensor);
	}
	else if (command == "set-notify") {
		if (sensor == "temperature") {
			// Estract value
			for (int i = 2; i < tokens.size(); i++) {
				String param_val = tokens[i];
				param_val.trim();

				int posSpace = param_val.indexOf(' ');
				if (posSpace <= 0) {
					error += param_val + " :Cannot be parsed\n";
				}
				else {
					String param = param_val.substring(0, posSpace);
					
					if (!std::count(PARAMS.begin(), PARAMS.end(), param)) {
						error += param + " Does NOT exists\n";
					}
				}
			}
		}
		else if (sensor == "humidity") {

		}
		else if (sensor == "co2") {

		}
		else if (sensor == "noise") {

		}
		else
			return (String("Cannot find sensor: ") + sensor);

		return "set-notify NOT yet implemented";
	}
	else {
		return "No get or set-notify as [0] element of tokens";
	}

	return error;
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

