/*
 Name:		CynexoArduinoNano33_CO2.ino
 Created:	3/31/2021 10:16:56 AM
 Author:	giovannirasera
*/
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
	String line{};

    if (central) {
        wasConnected = true;
        wasLocalNameDisplayed = false;

        Serial.print("BLE: Connected to central MAC: ");
        Serial.println(central.address());

		while (central.connected()) {
			if (Serial.available()) {
				line = Serial.readString();
				Serial.println(line);
				BLEService serv = serviceHandler.getBLEService(line);
				Serial.print("Characteristin is present: ");
				Serial.println(serv.hasCharacteristic("19B10001-E8F2-537E-4F6C-D104768A1214"));
				
			}
			
			delay(500);
		}

    }

    if (wasConnected) {
        Serial.print("Disconnected from MAC: ");
        Serial.println(central.address());
        wasConnected = false;
    }
}
