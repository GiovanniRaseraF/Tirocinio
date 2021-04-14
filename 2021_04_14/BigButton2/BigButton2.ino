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

#define LED1     2
#define LED2     4
#define LEDSTATE 3


long pressCounter = 0;
bool started = false;
bool logOnePrinted = false, logTwoPrinted = false;
unsigned long first = 0, second = 0, ledOn = 0;
int numberOfOptions = 2;
bool wasConnected = false;
String line = "";
PureCommand command{};


BLEService messageService{ "50B10000-E8F2-537E-4F6C-D104768A1214" };
BLEStringCharacteristic commandMessageCharacteristic{
    "19B10002-E8F2-537E-4F6C-D104768A1214",
    BLEWrite | BLERead,
    200
};

BLEService buttonService("19B10010-E8F2-537E-4F6C-D104768A1214");
BLELongCharacteristic cynexoBigButtonCharacteristic("19B10013-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLELongCharacteristic ledOnCharacteristic("19B10014-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLECharCharacteristic cynexoBigButtonEDGECharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

// Interrupt and debounce
void pressedBigButton(){
  static unsigned long lastInterruptTime = 0;
  unsigned long interruptTime = millis();
  
  if (interruptTime - lastInterruptTime > 1) {
    if(started)
      pressCounter++;
  }
  
  started = true;
  lastInterruptTime = interruptTime;
}

void reset(){
  wasConnected = false;
  digitalWrite(GREEN, HIGH);
  digitalWrite(RED, HIGH);
  digitalWrite(BLUE, LOW);
  cynexoBigButtonCharacteristic.writeValue(0);
  cynexoBigButtonEDGECharacteristic.writeValue('s');
  
  first = 0;
  second = 0;
  pressCounter = 0;
  started = false;
  ledOn = 0;
}

void setup(){
  pinMode( CynexoBigButton, INPUT_PULLUP );
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LEDSTATE, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(GREEN, HIGH);
  digitalWrite(BLUE, HIGH);
  digitalWrite(RED, HIGH);

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

  buttonService.addCharacteristic(cynexoBigButtonCharacteristic);
  buttonService.addCharacteristic(cynexoBigButtonEDGECharacteristic);
  buttonService.addCharacteristic(ledOnCharacteristic);
  messageService.addCharacteristic(commandMessageCharacteristic);
  BLE.addService(messageService);
  BLE.addService(buttonService);
  BLE.setLocalName("Cynexo Big Button");
  BLE.advertise();
  digitalWrite(BLUE, LOW);
  
  attachInterrupt( digitalPinToInterrupt( CynexoBigButton ), pressedBigButton, CHANGE );
}

void loop(){
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
        
        if(completeLine == "go;"){
           ledOn = millis();
           //ledOnCharacteristic.writeValue(ledOn);
           digitalWrite(LED1, HIGH);
        }else if(completeLine == "stop;"){
           digitalWrite(LED1, LOW);
        }
        completeLine = "";
        
        int pressCase = pressCounter % numberOfOptions;

        if(started){
          if(pressCase == 0 && !logOnePrinted){
            first = millis();
            cynexoBigButtonCharacteristic.writeValue(first);
            ledOnCharacteristic.writeValue(ledOn);
            cynexoBigButtonEDGECharacteristic.writeValue('r');
           
            logOnePrinted = true;
            logTwoPrinted = false;
            digitalWrite(RED, LOW);
          }
          else if(pressCase == 1 && !logTwoPrinted){
            second = millis();
            cynexoBigButtonCharacteristic.writeValue(second);
            ledOnCharacteristic.writeValue(ledOn);
            cynexoBigButtonEDGECharacteristic.writeValue('f');
            
            logOnePrinted = false;
            logTwoPrinted = true;
            digitalWrite(RED, HIGH);
          }
        }
      
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
