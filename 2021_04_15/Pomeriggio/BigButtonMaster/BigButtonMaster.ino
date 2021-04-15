#include <ArduinoBLE.h>
#include <Arduino.h>


/*
   tempo premuto
   tempo rilascio
   tempo led
*/
#define GREEN 23
#define BLUE  24
#define RED 22

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
  while (!Serial);
  Serial.println("Cynexo Big Button MASTER");

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

  BLE.scanForName("Cynexo Big Button");
  digitalWrite(BLUE, LOW);

}

void loop() {
  int prevFallingTimestamp = 0, prevRisingTimestamp = 0;
  int prevLedTimestamp = 0;
  int preCicles = 3000;
  BLEDevice peripheral = BLE.available();
  BLEService buttonService, messageService;
  BLECharacteristic commandMessageCharacteristic;
  BLECharacteristic cynexoBigButtonFALLINGCharacteristic;
  BLECharacteristic timeLedOnCharacteristic;
  BLECharacteristic cynexoBigButtonRISINGCharacteristic;

  if (peripheral) {
    Serial.print("Found ");
    Serial.println(peripheral.address());
    Serial.print(" '");
    Serial.println(peripheral.localName());

    // stop scanning
    BLE.stopScan();

    Serial.println("Connecting ...");

    if (peripheral.connect()) {
      Serial.println("Connected");
    } else {
      Serial.println("Failed to connect!");
      return;
    }

    // Services
    if (peripheral.discoverAttributes()) {
      Serial.println("Attributes discovered");
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

    // Comunication Started
    digitalWrite(BLUE, HIGH);
    bool canReadButton = false;
    bool newDelta = false;
    bool start = false;
    while (peripheral.connected()) {
      if (!preCicles) {
        if (!start)
          commandMessageCharacteristic.writeValue("go;");
        start = true;

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
              Serial.print("Delta: "); Serial.print(risingTimestamp - fallingTimestamp);
              Serial.print(" ,F: "); Serial.print(fallingTimestamp);
              Serial.print(" ,R: "); Serial.println(risingTimestamp);
              newDelta = false;
            }
          }
        }
      }
      else
        preCicles--;
    }
  }

  BLE.disconnect();
}
