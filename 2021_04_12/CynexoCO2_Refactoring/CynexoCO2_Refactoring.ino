/*
 Name:		CynexoCO2_Refactoring.ino
 Created:	4/7/2021 3:01:10 PM
 Author:	giovannirasera
*/
#include <ArduinoBLE.h>
#include <Arduino.h>
#include <Arduino_HTS221.h>
#include <Wire.h>
#include "SCD30.h"
#include "PureCommand.h"
#include "ServiceHandler.h"
#include "Tokenizer.h"
#define RED 22                    
#define BLUE 24            
#define GREEN 23      

ServiceHandler serviceHandler{BLE};
bool wasConnected = false;

void loop() {
	BLEDevice central = BLE.central();
	bool wasLocalNameDisplayed = false;
	unsigned long pastTime = millis(), currentTime = 0;
	String line = "", logged = "";
	int preCicles = 5000, prevDelayTime = 0;

	if (central) {
		wasConnected = true;
		wasLocalNameDisplayed = false;

		Serial.print("BLE: Connected to central MAC: ");
		Serial.println(central.address());

		while (central.connected()) {
			currentTime = millis();

			// Reading and updating
			line = serviceHandler.readLineFromBLE();
			logged = serviceHandler.update(line, currentTime, pastTime);
			if (logged != "")
				Serial.println(logged);
			
			// LOW POWER
			if (!preCicles) {
				delay(serviceHandler.delayTimeMillis);
				
				if (prevDelayTime != serviceHandler.delayTimeMillis) {
					Serial.print("Delay for LOW POWER: ");
					Serial.print(serviceHandler.delayTimeMillis / 1000);
					Serial.println(" seconds");
					prevDelayTime = serviceHandler.delayTimeMillis;
				}
			}
			// Pre LOW POWER
			else
				preCicles--;
		}
	}

	if (wasConnected) {
		Serial.print("Disconnected from MAC: ");
		Serial.println(central.address());
		wasConnected = false;
	}

}

void setup() {
  Wire.begin();
  
  pinMode(RED, OUTPUT);
  pinMode(BLUE, OUTPUT);
  pinMode(GREEN, OUTPUT);

  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, HIGH);
  
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
