#include <ArduinoBLE.h>
#include <Arduino.h>

#define GREEN 23
#define BLUE  24
#define RED 22



void setup() {
  Serial.begin(9600);
  while(!Serial);
  Serial.println("Cynexo Big Button MASTER");
  
  if(!BLE.begin()){
    // Blue Blinking if BLE does not work
    while(1){
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
  int preCicles = 5000;
  BLEDevice peripheral = BLE.available();
  BLEService buttonService, messageService;
  BLECharacteristic commandMessageCharacteristic;
  BLECharacteristic cynexoBigButtonCharacteristic;
  BLECharacteristic ledOnCharacteristic;
  BLECharacteristic cynexoBigButtonEDGECharacteristic;
 
  if(peripheral){
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
      cynexoBigButtonCharacteristic = buttonService.characteristic("19B10013-E8F2-537E-4F6C-D104768A1214");
      ledOnCharacteristic = buttonService.characteristic("19B10014-E8F2-537E-4F6C-D104768A1214");
      cynexoBigButtonEDGECharacteristic = buttonService.characteristic("19B10012-E8F2-537E-4F6C-D104768A1214");
      
      Serial.println("Button service discovered");
    }
    if (peripheral.discoverService("50B10000-E8F2-537E-4F6C-D104768A1214")) {
      messageService = peripheral.service("50B10000-E8F2-537E-4F6C-D104768A1214");
      commandMessageCharacteristic = messageService.characteristic("19B10002-E8F2-537E-4F6C-D104768A1214");
      
      Serial.println("Message service discovered");
    }
    digitalWrite(BLUE, HIGH);
    
    //commandMessageCharacteristic.writeValue("go;");
    bool start = false;
    while(peripheral.connected()){
      if(!preCicles){
        if(!start)
          commandMessageCharacteristic.writeValue("go;");
        start = true;
        byte timestamp;
        byte EDGE = 's';
        byte ledTimestamp;
        
        if(cynexoBigButtonCharacteristic.valueUpdated()){
            cynexoBigButtonCharacteristic.readValue(timestamp);
            Serial.print(" t: "); Serial.print(timestamp);
        }
        
        if(cynexoBigButtonEDGECharacteristic.valueUpdated()){
            cynexoBigButtonEDGECharacteristic.readValue(EDGE);
            Serial.print(" ,EDGE: "); Serial.print(EDGE);
        }
  
        if(ledOnCharacteristic.valueUpdated()){
            ledOnCharacteristic.readValue(ledTimestamp);
            Serial.print(" ,led: "); Serial.println(ledTimestamp);
        }
      }
      else
        preCicles--;
      //Serial.println();
      
    }

    BLE.scanForName("Cynexo Big Button");
    digitalWrite(BLUE, LOW);
  }
}
