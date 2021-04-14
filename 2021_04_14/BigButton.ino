#include <ArduinoBLE.h>
#define CynexoBigButton 5
#define GREEN 23
#define BLUE  24
#define RED 22 

long pressCounter = 0;
bool started = false;
bool logOnePrinted = false, logTwoPrinted = false;
unsigned long first = 0, second = 0;
int numberOfOptions = 2;
bool wasConnected = false;

BLEService buttonService("19B10010-E8F2-537E-4F6C-D104768A1214");
BLELongCharacteristic CynexoBigButtonCharacteristic("19B10013-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
BLECharCharacteristic CynexoBigButtonEDGECharacteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);

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
  CynexoBigButtonCharacteristic.writeValue(0);
  CynexoBigButtonEDGECharacteristic.writeValue('s');
  
  first = 0;
  second = 0;
  pressCounter = 0;
  started = false;
}

void setup(){
  pinMode( CynexoBigButton, INPUT_PULLUP );
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

  buttonService.addCharacteristic(CynexoBigButtonCharacteristic);
  buttonService.addCharacteristic(CynexoBigButtonEDGECharacteristic);
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

  //Comunication
  if (central) {
    digitalWrite(GREEN, HIGH);
    digitalWrite(BLUE, HIGH);
    wasConnected = true;
    wasLocalNameDisplayed = false;

    while (central.connected()) {
        int pressCase = pressCounter % numberOfOptions;

        if(started){
          if(pressCase == 0 && !logOnePrinted){
            first = millis();
            CynexoBigButtonCharacteristic.writeValue(first);
            CynexoBigButtonEDGECharacteristic.writeValue('r');
            
            logOnePrinted = true;
            logTwoPrinted = false;
            digitalWrite(RED, LOW);
          }
          else if(pressCase == 1 && !logTwoPrinted){
            second = millis();
            CynexoBigButtonCharacteristic.writeValue(second);
            CynexoBigButtonEDGECharacteristic.writeValue('f');
            
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