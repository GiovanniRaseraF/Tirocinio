//#include <ArduinoBLE.h>
#define ENABLE  12
#define MS1     11
#define MS2     10
#define MS3      9
#define STEPS    8
#define DIR      7

#define BUTTON1  5
#define BUTTON2  6

#define LED1     2
#define LED2     4
#define LEDSTATE 3

#define BATTERY  A0 //digital signal
#define BUZZER   A1 //pwm 
#define LIGHT_M  A2
#define REWARD   A3
#define SYNC_IN  A4
#define SYNC_OUT A5
#define DE       A6
#define RE       A7

//BLEService buttonService("19B10010-E8F2-537E-4F6C-D104768A1214");
//BLEByteCharacteristic button1Characteristic("19B10013-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
//BLEByteCharacteristic button2Characteristic("19B10012-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
//BLEUnsignedIntCharacteristic deltaTimeCharacteristic("19B10014-E8F2-537E-4F6C-D104768A1214", BLERead | BLENotify);
bool wasConnected = false;
volatile int count1 = 0, count2 = 0;
unsigned long firstMillis1 = 0;
unsigned long secondMillis1 = 0;
unsigned long firstMillis2 = 0;
unsigned long secondMillis2 = 0;

void loop() {
  //int uno = digitalRead(BUTTON1);
  //int due = digitalRead(BUTTON2);
  //Serial.print(uno);Serial.print("   "); Serial.println(due);
  //Serial.println(firstMillis1);
  //delay(10);
   if(count1 == 3 ){
    Serial.println("Premuto 3 volte");
    count1 = 0;
   }
    
    
    /*BLEDevice central = BLE.central();
    bool wasLocalNameDisplayed = false;

    if (central) {
      wasConnected = true;
      wasLocalNameDisplayed = false;

      Serial.print("BLE: Connected to central MAC: ");
      Serial.println(central.address());

      while (central.connected());
      
    }

    if (wasConnected) {
      Serial.print("Disconnected from MAC: ");
      Serial.println(central.address());
      wasConnected = false;
    }*/
}

void saveMillis1(){
  count1++; 
}


void setup() {
  // BLE init
  Serial.begin(9600);
  
  pinMode(BUTTON2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(BUTTON2), saveMillis1, FALLING);
 
  
  
  //if(!BLE.begin()){
  //  Serial.println("BLE init fail!");
  //  while(1);
 // }

 // buttonService.addCharacteristic(button2Characteristic);
 // buttonService.addCharacteristic(button1Characteristic);
//  //buttonService.addCharacteristic(deltaTimeCharacteristic);
 // BLE.addService(buttonService);
  
 // BLE.setLocalName("Cynexo Big Push Button");
//Serial.print("BLE started at: "); Serial.println(BLE.address());

 // BLE.advertise();
 // Serial.println("BLE: Waiting for connections...");
}

/*
// Define Pin out
  pinMode(ENABLE, OUTPUT);
  pinMode(MS1, OUTPUT);
  pinMode(MS2, OUTPUT);
  pinMode(MS3, OUTPUT);
  pinMode(STEPS, OUTPUT);
  pinMode(DIR, OUTPUT);
  
  pinMode(BUTTON2, INPUT);

  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LEDSTATE, OUTPUT);

  pinMode(BATTERY, INPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(LIGHT_M, INPUT);
  pinMode(REWARD, OUTPUT);

  pinMode(SYNC_IN, INPUT);
  pinMode(SYNC_OUT, OUTPUT);

  pinMode(RE, OUTPUT);
  pinMode(DE, OUTPUT);
  
  
  */
