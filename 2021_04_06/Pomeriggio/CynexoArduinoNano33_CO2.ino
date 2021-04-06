/*
 Name:		CynexoArduinoNano33_CO2.ino
 Created:	3/31/2021 10:16:56 AM
 Author:	giovannirasera
*/
#include <Wire.h>
#include <Arduino_HTS221.h>
#include <ArduinoBLE.h>
#include "ServiceHandler.h"
#include <tuple>
#include "Interpreter.h"

ServiceHandler serviceHandler(BLE);
Interpreter interpreter{};
bool wasConnected = false;

void setup() {
	// Serial init
	Serial.begin(9600);
	while (!Serial);
	// BLE init
	if (!BLE.begin()) {
		Serial.println("BLE: Start Failed!");
		while (1);
	}
	BLE.setLocalName("CynexoC02");

	// HTS init
	if (!HTS.begin()) {
		Serial.println("HTS: Start Failed!");
		while (1);
	}
	//readHTS221Calibration();

	Serial.print("BLE: Started at: ");
	Serial.println(BLE.address());

	serviceHandler.start();
	Serial.println("ServiceHandler: Started");

	BLE.advertise();
	Serial.println("BLE: Waiting for connections...");
}


void loop() {
	BLEDevice central = BLE.central();
	bool wasLocalNameDisplayed = false;
	String line;
	//Service serv;

    if (central) {
        wasConnected = true;
        wasLocalNameDisplayed = false;

        Serial.print("BLE: Connected to central MAC: ");
        Serial.println(central.address());
		
		while (central.connected()) {
			/*if (Serial.available()) {
				line = Serial.readString();
				line.trim();
				Serial.print("Serial: Command ->");
				Serial.println(line);

				if (line == "temperature") {
					float temperature = serviceHandler.readTemperature();
					Serial.print("Serial: Temperature: ");
					Serial.println(temperature);
				}

				if (line == "humidity") {
					float humidity = serviceHandler.readHumidity();
					Serial.print("Serial: Humidity: ");
					Serial.println(humidity);
				}

				if (line == "message") {
					serviceHandler.writeLogReport("hello");
				}

				if (line == "command") {
					String command = serviceHandler.readCommand();
					Serial.println(command);

					std::vector<String> tokens = interpreter.tokenize(command);
					for (String t : tokens)
						Serial.println(t);
				}

			}*/
			//Read command
			String command = serviceHandler.readCommand();
			if (command != "") {
				std::vector<String> tokens = interpreter.tokenize(command);
				
				/*for (String t : tokens)
					Serial.println(t);*/
				if (!tokens.empty()) {
					String error = serviceHandler.executeParsedCommand(tokens);
					if (error != "") {
						Serial.println(error);
					}
				}
			}

			String res = serviceHandler.update();
			if(res != "")
				Serial.println(res);
		}
    }

    if (wasConnected) {
        Serial.print("Disconnected from MAC: ");
        Serial.println(central.address());
        wasConnected = false;
    }
}
