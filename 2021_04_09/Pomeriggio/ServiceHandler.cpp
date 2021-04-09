#include "ServiceHandler.h"

ServiceHandler::ServiceHandler(BLELocalDevice& B) : BLE{ B }{}

bool ServiceHandler::start(void) {
	//messageService.addCharacteristic(logReportMessageCharacteristic);
	messageService.addCharacteristic(commandMessageCharacteristic);
	BLE.setAdvertisedService(messageService);
	BLE.addService(messageService);

	environmentService.addCharacteristic(temperatureCharacteristic);
	environmentService.addCharacteristic(humidityCharacteristic);
	BLE.setAdvertisedService(environmentService);
	BLE.addService(environmentService);

	return true;
}

float ServiceHandler::readTemperature(void) {
	int cicles = 1;
	float temperature = 0;

	for (int i = 0; i < cicles; i++) {
		temperature += HTS.readTemperature();
		delay(100);
	}
	temperature = (temperature / cicles) - TEMPERATURE_OFFSET;

	return temperature;
}

bool ServiceHandler::notifyTemperature(float temperature) {
	temperatureCharacteristic.writeValueLE(temperature * 100);
	
	return true;
}

float ServiceHandler::readHumidity(void) {
	int cicles = 1;
	float humidity = 0;

	for (int i = 0; i < cicles; i++) {
		humidity += HTS.readHumidity();
		//delay(100);
	}
	humidity = (humidity / cicles);

	return humidity;
}

bool ServiceHandler::notifyHumidity(float humidity) {
	humidityCharacteristic.writeValueLE(humidity * 100);

	return true;
}

bool ServiceHandler::writeLogReport(String& message) {
	logReportMessageCharacteristic.writeValue(message);

	return true;
}

String ServiceHandler::readLineFromBLE(void) {
	String ret = "";

	if (commandMessageCharacteristic.written()) {
		this->line += commandMessageCharacteristic.value();
		if (Tokenizer::doesLineEnds(this->line)) {
			ret = this->line;
			ret.trim();
			this->line = "";
		}
	}

	return ret;

}

String ServiceHandler::executePureCommand(PureCommand& command) {
	// Get
	if ("get" == command.primary) {
		if ("temperature" == command.sensor) {
			float temperature = readTemperature();
			notifyTemperature(temperature);

			return "Temperature notified: " + String(temperature);
		}
		else if ("humidity" == command.sensor) {
			float humidity = readHumidity();
			notifyHumidity(humidity);

			return "Humidity notified: " + String(humidity);
		}
		else {
			return "Sensor: " + command.sensor + "does NOT exists";
		}
	}
	// Set-notify
	else if ("set-notify" == command.primary) {
		if ("temperature" == command.sensor) {
			temperatureEvent.setNotify(command);

			return "Updated NOTIFY ON Temperature";
		}
		else if ("humidity" == command.sensor) {
			humidityEvent.setNotify(command);

			return "Updated NOTIFY ON Humidity";
		}
		else {
			return "Sensor: " + command.sensor + "does NOT exists";
		}
	}
	// Reset-notify
	else if ("reset-notify" == command.primary) {
		if ("temperature" == command.sensor) {
			temperatureEvent.setNewNotify(temperatureDefault);

			return "RESET NOTIFY ON Temperature";
		}
		else if ("humidity" == command.sensor) {
			humidityEvent.setNewNotify(humidityDefault);

			return "RESET NOTIFY ON Humidity";
		}
		else {
			return "Sensor: " + command.sensor + "does NOT exists";
		}
	}
	// Set-delay
	else if ("set-delay" == command.primary) {
		if ("lowpower" == command.sensor) {
			float timedelay = command.get("time");

			if (timedelay < MIN_DELAY_LOWPOWER)
				return "CANNOT update LOW POWER delay < " + String(MIN_DELAY_LOWPOWER);
			if (timedelay == PARAM_NOT_SET)
				return "CANNOT update LOW POWER delay";
			this->delayTimeMillis = floor(timedelay);

			return "Updated LOW POWER delay";
		}
		else {
			return "Set-delay Wrong, use: set-delay lowpower (time 10000);";
		}
	}
	else {
		return "Primary: [" + command.primary + "] NOT VALID";
	}

	return "";
}

String ServiceHandler::update(String& line, unsigned long& currentTime, unsigned long& pastTime) {
	PureCommand command;
	String ret = "";
	float temperature = 0, humidity = 0;
	if ((currentTime - pastTime) < delayTimeMillis / 2)
		return "";

	// Notification
	temperature = readTemperature();
	humidity = readHumidity();
	if (temperatureEvent.checkNotify(temperature, millis())) {
		ret += "Temp Notified, ";
		notifyTemperature(temperature);
	}
	if (humidityEvent.checkNotify(humidity, millis())) {
		ret += "Hum Notified, ";
		notifyHumidity(humidity);
	}
	

	if (line == "")
		return ret;
	pastTime = currentTime;

	// Command execution
	command = Tokenizer::createCommand(line);
	ret += executePureCommand(command);

	
	
	return ret;
}