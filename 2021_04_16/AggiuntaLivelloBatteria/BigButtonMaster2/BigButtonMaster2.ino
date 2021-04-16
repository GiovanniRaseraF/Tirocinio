#include <ArduinoBLE.h>
#include <Arduino.h>
#include "Tokenizer.h"

#define GREEN 23
#define BLUE  24
#define RED 22

String line = "";
boolean stringComplete = false;

int prevFallingTimestamp = 0;
int prevRisingTimestamp = 0;
int prevLedTimestamp = 0;
int preCicles = 3000;

BLEService buttonService, messageService, batteryService;
BLECharacteristic commandMessageCharacteristic;
BLECharacteristic cynexoBigButtonFALLINGCharacteristic;
BLECharacteristic timeLedOnCharacteristic;
BLECharacteristic cynexoBigButtonRISINGCharacteristic;
BLECharacteristic batteryLevelBool;

// Utils
union ArrayToInteger {
  byte array[4];
  uint32_t integer;
};

int byteArrayToInt(const byte data[], int length) {
  byte dataW[length];

  for (int i = 0; i < length; i++) {
    byte b = data[i];
    dataW[i] = data[i];
  }

  ArrayToInteger converter; //Create a converter
  converter.array[0] = dataW[0];
  converter.array[1] = dataW[1];
  converter.array[2] = dataW[2];
  converter.array[3] = dataW[3];

  return converter.integer ;
}

bool valueChanged(int preVal, int newVal) {
  return preVal != newVal;
}

void setup() {
  Serial.begin(9600);
  //while (!Serial);
  //Serial.println("Cynexo Big Button MASTER");

  if (!BLE.begin()) {
    Serial.println("Ble error");
    while (1);
  }

  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);

  // Start scanning
  BLE.scanForName("Cynexo Big Button");
  digitalWrite(BLUE, LOW);
}

void loop() {
  BLEDevice peripheral = BLE.available();

  if (peripheral) {
    Serial.print("Found "); Serial.println(peripheral.localName());

    // stop scanning
    BLE.stopScan();
    if (peripheral.connect())
      Serial.println("Connected");

    // Services
    if (peripheral.discoverAttributes())
      Serial.println("Attributes discovered");

    if (peripheral.discoverService("180F")) {
      batteryService = peripheral.service("180F");
      batteryLevelBool = batteryService.characteristic("19B10020-E8F2-537E-4F6C-D104768A1214");

      Serial.println("Battery service discovered");
    }
    if (peripheral.discoverService("19B10010-E8F2-537E-4F6C-D104768A1214")) {
      buttonService = peripheral.service("19B10010-E8F2-537E-4F6C-D104768A1214");
      cynexoBigButtonFALLINGCharacteristic = buttonService.characteristic("19B10013-E8F2-537E-4F6C-D104768A1214");
      timeLedOnCharacteristic = buttonService.characteristic("19B10014-E8F2-537E-4F6C-D104768A1214");
      cynexoBigButtonRISINGCharacteristic = buttonService.characteristic("19B10012-E8F2-537E-4F6C-D104768A1214");

      Serial.println("Button service discovered");
    }
    if (peripheral.discoverService("50B10000-E8F2-537E-4F6C-D104768A1214")) {
      messageService = peripheral.service("50B10000-E8F2-537E-4F6C-D104768A1214");
      commandMessageCharacteristic = messageService.characteristic("19B10002-E8F2-537E-4F6C-D104768A1214");

      Serial.println("Message service discovered");
    }

    bool canReadButton = false;
    bool newDelta = false;
    bool start = false;
    String serialLine = "";

    // Comunication Started
    digitalWrite(BLUE, HIGH);
    while (peripheral.connected()) {
      if (!preCicles) {
        // Read from serial
        serialLine = readLineFromSerial();
        // Commands interpretation
        if (serialLine != "") {
          if (serialLine == "go;") {
            start = true;
            Serial.println("--Go--");
          } else if (serialLine == "stop;") {
            start = false;
            prevFallingTimestamp = 0;
            prevRisingTimestamp = 0;
            prevLedTimestamp = 0;
            canReadButton = false;
            Serial.println("--Stop--");
          }
          // Send command
          commandMessageCharacteristic.writeValue(serialLine.c_str());

          // Read battery level
          batteryLevelBool.read();
          bool batteryLevel = byteArrayToInt(batteryLevelBool.value(), batteryLevelBool.valueLength());
          if(batteryLevel){
            Serial.println("Battery GOOD");
          }else{
            Serial.println("!!!!!! Battery LOW !!!!!!");
          }
        }

        if (start) {
          // Led time
          timeLedOnCharacteristic.read();
          int newLedTimestamp = byteArrayToInt(timeLedOnCharacteristic.value(), timeLedOnCharacteristic.valueLength());
          if (valueChanged(prevLedTimestamp, newLedTimestamp) && newLedTimestamp != 0) {
            Serial.print("Led init: "); Serial.println(newLedTimestamp);
            prevLedTimestamp = newLedTimestamp;
            canReadButton = true;
          }

          if (canReadButton) {
            // Button time
            cynexoBigButtonFALLINGCharacteristic.read();
            cynexoBigButtonRISINGCharacteristic.read();

            int fallingTimestamp = byteArrayToInt(cynexoBigButtonFALLINGCharacteristic.value(), cynexoBigButtonFALLINGCharacteristic.valueLength());
            int risingTimestamp = byteArrayToInt(cynexoBigButtonRISINGCharacteristic.value(), cynexoBigButtonRISINGCharacteristic.valueLength());

            if (fallingTimestamp != 0 && risingTimestamp != 0 &&
                (valueChanged(prevFallingTimestamp, fallingTimestamp) && valueChanged(prevRisingTimestamp, risingTimestamp))) {

              newDelta = true;
              prevFallingTimestamp = fallingTimestamp;
              prevRisingTimestamp = risingTimestamp;
            }

            if (fallingTimestamp < risingTimestamp) {
              if (newDelta) {
                // new data will be available here
                Serial.print("Delta: ");
                Serial.print(risingTimestamp - fallingTimestamp);
                Serial.print(" ,F: "); Serial.print(fallingTimestamp);
                Serial.print(" ,R: "); Serial.println(risingTimestamp);

                newDelta = false;
              }
            }
          }
        }
      } else {
        preCicles--;
      }

    }
  }

  prevFallingTimestamp = 0;
  prevRisingTimestamp = 0;
  prevLedTimestamp = 0;
  preCicles = 3000;

  BLE.disconnect();
  //Serial.println("Disconnected");
  BLE.scanForName("Cynexo Big Button");
  digitalWrite(BLUE, LOW);
  //Serial.println("Scanning");
}

String readLineFromSerial(void) {
  String ret = "";

  if (Serial.available() > 0) {
    line += Serial.readString();
    if (Tokenizer::doesLineEnds(line)) {
      ret = line;
      ret.trim();
      line = "";
    }
  }

  return ret;
}
