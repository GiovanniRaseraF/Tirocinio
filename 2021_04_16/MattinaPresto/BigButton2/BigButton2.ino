#include <ArduinoBLE.h>
#include <vector>
#include <tuple>
#include <Arduino.h>
#include <functional>
#include <algorithm>
#include <time.h>
#include "PureCommand.h"
#include "Tokenizer.h"

#define CynexoBigButton 5

#define GREEN 23
#define BLUE  24
#define RED 22
#define BATTERY  A0 //digital signal

#define LED1     2
#define LED2     4
#define LEDSTATE 3

long pressCounter = 0;
bool started = false;
bool state = true;
bool logFALLINGNotified = false, logRISINGNotified = false;
unsigned long first = 0, second = 0, timeLedOn = 0;
int timeFALLING = 0, timeRISING = 0;
int numberOfOptions = 2;
bool wasConnected = false;
String line = "";
int oldBatteryLevel = 0;

BLEService batteryService("180F");
BLEBoolCharacteristic batteryLevelBool("19B10020-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

BLEService messageService{ "50B10000-E8F2-537E-4F6C-D104768A1214" };
BLEStringCharacteristic commandMessageCharacteristic{
  "19B10002-E8F2-537E-4F6C-D104768A1214",
  BLEWrite | BLERead,
  200
};

BLEService buttonService("19B10010-E8F2-537E-4F6C-D104768A1214");
BLELongCharacteristic cynexoBigButtonFALLINGCharacteristic("19B10013-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLELongCharacteristic timeLedOnCharacteristic("19B10014-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLELongCharacteristic cynexoBigButtonRISINGCharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

// Interrupt and debounce
void button_low_isr() {
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();

  if (interruptTime - lastInterruptTime > 10) {
    if (started) {
      if (state) {
        timeFALLING = millis();
        logFALLINGNotified = false;
      } else {
        timeRISING = millis();
        logRISINGNotified = false;
      }
      state = !state;
    }
  }

  lastInterruptTime = interruptTime;
}

void reset() {
  wasConnected = false;
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, LOW);
  digitalWrite(LED1, LOW);
  cynexoBigButtonRISINGCharacteristic.writeValue(0);
  cynexoBigButtonFALLINGCharacteristic.writeValue(0);

  first = 0;
  second = 0;
  pressCounter = 0;
  started = false;
  timeLedOn = 0;
}

void setup() {
  pinMode( CynexoBigButton, INPUT_PULLUP );
  //digitalWrite(CynexoBigButton, HIGH);
  pinMode(LED1, OUTPUT);

  pinMode(BATTERY, INPUT);

  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);

  if (!BLE.begin()) {
    // Blue Blinking if BLE does not work
    while (1) {
      digitalWrite(BLUE, HIGH);
      delay(200);
      digitalWrite(BLUE, LOW);
      delay(200);
    }
  }
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);

  batteryService.addCharacteristic(batteryLevelBool);
  buttonService.addCharacteristic(cynexoBigButtonFALLINGCharacteristic);
  buttonService.addCharacteristic(cynexoBigButtonRISINGCharacteristic);
  buttonService.addCharacteristic(timeLedOnCharacteristic);
  messageService.addCharacteristic(commandMessageCharacteristic);
  BLE.setAdvertisedService(buttonService);
  BLE.setAdvertisedService(messageService);
  BLE.setAdvertisedService(batteryService);
  BLE.addService(batteryService);
  BLE.addService(messageService);
  BLE.addService(buttonService);

  BLE.setLocalName("Cynexo Big Button");
  BLE.advertise();
  digitalWrite(BLUE, LOW);

  attachInterrupt( digitalPinToInterrupt( CynexoBigButton ), button_low_isr,  CHANGE);
}

void loop() {
  BLEDevice central = BLE.central();
  bool wasLocalNameDisplayed = false;
  unsigned long pastTime = millis(), currentTime = 0;
  int preCicles = 5000;
  String completeLine = "";

  //Comunication
  if (central) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    wasConnected = true;
    wasLocalNameDisplayed = false;

    while (central.connected()) {
      completeLine = readLineFromBLE();
      if (completeLine == "go;") {
        updateBatteryLevel();
        timeLedOn = millis();
        timeLedOnCharacteristic.writeValue(timeLedOn);
        started = true;
        digitalWrite(LED1, HIGH);
      } else if (completeLine == "stop;") {
        started = false;
        timeFALLING = 0;
        timeRISING = 0;
        logFALLINGNotified = false;
        logRISINGNotified = false;
        cynexoBigButtonFALLINGCharacteristic.writeValue(0);
        cynexoBigButtonRISINGCharacteristic.writeValue(0);
        digitalWrite(LED1, LOW);
      }

      completeLine = "";

      int pressCase = pressCounter % numberOfOptions;

      if (started) {
        if (timeFALLING != 0 && !logFALLINGNotified) {
          cynexoBigButtonFALLINGCharacteristic.writeValue(timeFALLING);

          timeFALLING = 0;
          logFALLINGNotified = true;
        }
        if (timeRISING != 0 && !logRISINGNotified) {
          cynexoBigButtonRISINGCharacteristic.writeValue(timeRISING);

          timeRISING = 0;
          logRISINGNotified = true;
        }
      }

      //noInterrupts();
      // Try to backup the state
      state = digitalRead(CynexoBigButton);
      //interrupts();

    }
  }

  if (wasConnected) {
    reset();
  }
}

String readLineFromBLE(void) {
  String ret = "";

  if (commandMessageCharacteristic.written()) {
    line += commandMessageCharacteristic.value();
    if (Tokenizer::doesLineEnds(line)) {
      ret = line;
      ret.trim();
      line = "";
    }
  }

  return ret;
}

void updateBatteryLevel() {
  bool battery = digitalRead(A0);
  batteryLevelBool.writeValue(battery);
}
