#include "ServiceHandler.h"

ServiceHandler::ServiceHandler(BLELocalDevice& B) : BLE{ B }{}

bool ServiceHandler::start(void) {
  // HTC sensor
  scd30.setAutoSelfCalibration(1);
  scd30.initialize();
  
	//messageService.addCharacteristic(logReportMessageCharacteristic);
	messageService.addCharacteristic(commandMessageCharacteristic);
	BLE.setAdvertisedService(messageService);
	BLE.addService(messageService);

	environmentService.addCharacteristic(temperatureCharacteristic);
	environmentService.addCharacteristic(humidityCharacteristic);
  environmentService.addCharacteristic(co2Characteristic);
	BLE.setAdvertisedService(environmentService);
	BLE.addService(environmentService);

	return true;
}

float ServiceHandler::readTemperature(void) {
	int cicles = 1;
	float temperature = 0;
  if(scd30.isAvailable())
    scd30.getCarbonDioxideConcentration(resultHTC);
  
	for (int i = 0; i < cicles; i++) {
		temperature += resultHTC[1];
		delay(10);
	}
	temperature = (temperature / cicles);

	return temperature;
}

bool ServiceHandler::notifyTemperature(float temperature) {
	temperatureCharacteristic.writeValueLE(temperature * 100);
	
	return true;
}

float ServiceHandler::readHumidity(void) {
	int cicles = 1;
	float humidity = 0;
  if(scd30.isAvailable())
    scd30.getCarbonDioxideConcentration(resultHTC);
    
	for (int i = 0; i < cicles; i++) {
		humidity += resultHTC[2];
		delay(10);
	}
	humidity = (humidity / cicles);

	return humidity;
}

bool ServiceHandler::notifyHumidity(float humidity) {
	humidityCharacteristic.writeValueLE(humidity * 100);

	return true;
}

float ServiceHandler::readCo2(){
  int cicles = 1;
  float co2 = 0;
  if(scd30.isAvailable())
    scd30.getCarbonDioxideConcentration(resultHTC);

  for (int i = 0; i < cicles; i++) {
    co2 += resultHTC[0];
    delay(10);
  }
  co2 = (co2 / cicles);

  return co2;
}

bool ServiceHandler::notifyCo2(float co2){
  co2Characteristic.writeValueLE(co2 * 100);
}

/* Danger levels            Color               Min     Max
// Good                     Green               Below   1000
// Attention                Yellow              1000    1400
// More attention           Yellow blinking     1400    2000
// Bad                      Red    blinking     2000    Above*/
void ServiceHandler::blinkDangerLed(float co2){
  if(co2 <= 1000){
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  }else if(1000 < co2 && co2 <= 1400){
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
  }else if(1400 < co2 && co2 <= 2000){
    for(int i = 0; i < 5; i++){
      digitalWrite(BLUE, LOW);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      delay(100);
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      delay(100);
    }
  }else{
    for(int i = 0; i < 5; i++){
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      delay(100);
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      delay(100);
    }
  }
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
		else if ("co2" == command.sensor){
			float co2 = readCo2();
			notifyCo2(co2);
			
			return "Co2 notified: " + String(co2);
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
		else if ("co2" == command.sensor){
			co2Event.setNotify(command);

			return "Updated NOTIFY ON co2";
		}
		else {
			return "Sensor: " + command.sensor + " does NOT exists";
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
		else if ("co2" == command.sensor){
			co2Event.setNotify(co2Default);
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
	float temperature = 0, humidity = 0, co2 = 0;
	if ((currentTime - pastTime) < delayTimeMillis)
		return "";

	// Sensor reading
	while(!scd30.isAvailable());
  scd30.getCarbonDioxideConcentration(resultHTC);
  co2           = resultHTC[0];
  temperature   = resultHTC[1];
  humidity      = resultHTC[2];

  // Notification and blinking danger
  blinkDangerLed(co2);

	if (temperatureEvent.checkNotify(temperature, millis())) {
		notifyTemperature(temperature);
   
    ret += "\nTemperature: " + String(temperature);
	}
	if (humidityEvent.checkNotify(humidity, millis())) {
		notifyHumidity(humidity);
   
    ret += "\nHumidity: " + String(humidity);
	}
  if (co2Event.checkNotify(co2, millis())){
    notifyCo2(co2);
    
    ret += "\nCo2: " + String(co2);
  }
	
	if (line == "")
		return ret;
	pastTime = currentTime;

	// Command execution
	command = Tokenizer::createCommand(line);
	ret += "\n" + executePureCommand(command);

	return ret;
}
