#include <ArduinoBLE.h>

static const char* greeting = "Hello World!";
BLEService greetingService("180C");  // User defined service
BLEStringCharacteristic greetingCharacteristic("2A56",  // standard 16-bit characteristic UUID
    BLERead , 13); // remote clients will only be able to read this
bool wasConnected = false;

void setup() {
    Serial.begin(9600);
    while (!Serial);

    // begin initialization
    if (!BLE.begin()) {
        Serial.println("Starting BLE failed!");
        while (1);
    }

    Serial.println("BLE Central scan");
    BLE.setLocalName("CynexoArduinoNano33BLE");
    BLE.setAdvertisedService(greetingService);
    greetingService.addCharacteristic(greetingCharacteristic);
    BLE.addService(greetingService);
    greetingCharacteristic.setValue(greeting);

    BLE.advertise();
    Serial.print("Peripheral device MAC: ");
    Serial.println(BLE.address());
    Serial.println("Waiting for connections...");
}

void loop() {
    BLEDevice central = BLE.central();
    bool wasLocalNameDisplayed = false;

    if (central) {
        wasConnected = true;
        wasLocalNameDisplayed = false;
        
        Serial.print("Connected to central MAC: ");
        Serial.println(central.address());

        while (central.connected()) {
            if (central.hasLocalName() && !wasLocalNameDisplayed) {
                Serial.print("Local Name: ");
                Serial.println(central.localName());
                wasLocalNameDisplayed = true;
                
            }
            
            //if(greetingCharacteristic.canWrite())
            //greetingCharacteristic.writeValue(greeting);
            
            delay(100000);
        }
    }

    if (wasConnected) {
        Serial.print("Disconnected from MAC: ");
        Serial.println(central.address());
        wasConnected = false;
    }
  
}