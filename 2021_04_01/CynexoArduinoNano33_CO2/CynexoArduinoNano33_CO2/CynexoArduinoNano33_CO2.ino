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

ServiceHandler serviceHandler(BLE);
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
			if (Serial.available()) {
				line = Serial.readString();
				line.trim();
				Serial.print("Serial: Command ->");
				Serial.println(line);

				if (line == "temperature") {
					float temperature = serviceHandler.readTemperature();
					Serial.print("Temperature: ");
					Serial.println(temperature);
				}

				if (line == "message") {
					serviceHandler.writeLogReport("hello");
					Serial.println("Message: sent");
				}

				if (line == "command") {
					String command = serviceHandler.readCommand();
					Serial.println(command);
				}

			}
			
			//delay(500);
		}
    }

    if (wasConnected) {
        Serial.print("Disconnected from MAC: ");
        Serial.println(central.address());
        wasConnected = false;
    }
}
