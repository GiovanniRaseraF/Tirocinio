#include <mbed.h>
#include <ArduinoBLE.h>
#include <rtos.h>
#include <mbed_wait_api.h>
#include <platform/CircularBuffer.h>
#include <platform/Callback.h>
#include <Wire.h>
#include <queue>
#include <vector>
#include "SCD30.h"

#define BUFF_SIZE 144

#define RED 3
#define GREEN 2

#define Good 0
#define Attention 1
#define MoreAttention 2
#define Bad 3

class reading {
  public:
    float temperature = 0;
    float humidity = 0;
    float co2 = 0;
    reading(float c, float h, float t) {
      co2 = c;
      humidity = h;
      temperature = t;
    }
    ~reading() {};
};

float temperature = 0, humidity = 0, co2 = 0;
float resultHTC[3] = {0};

// Threading
using namespace rtos;
Mutex resourceHandle;
std::queue<reading> buff;
char sensor[7] = {'S', 'e', 'n', 's', 'o' , 'r', '\0'};
char light[4] = {'L', 'e', 'd', '\0'};
char bluez[4] = {'B', 'L', 'E', '\0'};
Thread lights;
Thread sampling;
Thread bluetooth;


long timeDelay = 1000;
int cicles = 0;
int states = 0;

// Arduino Specific
void setup() {
  BLE.begin();
  Wire.begin();
  Serial.begin(9600);
  delay(2000);
  Serial.println("CynexoCo2 Threading Version");
  
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  digitalWrite(RED, LOW);
  digitalWrite(GREEN, LOW);
  scd30.initialize();
  scd30.setAutoSelfCalibration(1);

  sampling.start(mbed::callback(updateReadingsFromSCD30, sensor));
  lights.start(mbed::callback(displayInformationToLed, light));
  bluetooth.start(mbed::callback(bluetoothHandler, bluez));
}

void loop() {

}
// Thread specific
void updateReadingsFromSCD30(char* val) {
  for (;;) {
    if (scd30.isAvailable()) {
      scd30.getCarbonDioxideConcentration(resultHTC);
      co2           = resultHTC[0];
      temperature   = resultHTC[1];
      humidity      = resultHTC[2];

      if (!isnan(co2) && !isnan(temperature) && !isnan(humidity)) {
        states = selectState(co2);
        /*
          Serial.print(co2); Serial.print(",");
          Serial.print(temperature); Serial.print(",");
          Serial.print(humidity); Serial.print("");
          Serial.println("");
        */
        resourceHandle.lock();
        buff.push({co2, humidity, temperature});
        resourceHandle.unlock();
      }
    }
  }
}

/* Danger levels            Color               Min     Max
  // Good                     Green               Below   1000
  // Attention                Yellow              1000    1400
  // More attention           Yellow blinking     1400    2000
  // Bad                      Red    blinking     2000    Above*/
void displayInformationToLed(char* val) {
  for (;;) {
    switch (states) {
      case Good:
        digitalWrite(RED, LOW);
        digitalWrite(GREEN, HIGH);
        delay(timeDelay);
        break;
      case Attention:
        digitalWrite(RED, LOW);
        for (int i = 0; i < timeDelay / 1000; i++) {
          digitalWrite(GREEN, HIGH);
          delay(timeDelay / (timeDelay / 1000));
          digitalWrite(GREEN, LOW);
          delay(timeDelay / (timeDelay / 1000));
        }
        break;
      case MoreAttention:
        digitalWrite(GREEN, LOW);
        digitalWrite(RED, HIGH);
        delay(timeDelay);
        break;
      case Bad:
        digitalWrite(GREEN, LOW);
        for (int i = 0; i < timeDelay / 100; i++) {
          digitalWrite(RED, HIGH);
          delay(timeDelay / (timeDelay / 100));
          digitalWrite(RED, LOW);
          delay(timeDelay / (timeDelay / 100));
        }
        break;
    }
  }
}

void bluetoothHandler(char* val) {
  for (;;) {
    delay(5000);
    if (buff.size() > 10) {
      resourceHandle.lock();
      while (!buff.empty()) {
        reading r = buff.front();

        Serial.print(r.co2); Serial.print(",");
        Serial.print(r.temperature); Serial.print(",");
        Serial.print(r.humidity); Serial.print("");
        Serial.println("");

        buff.pop();
      }
      resourceHandle.unlock();
    }
  }
}

int selectState(float co2) {
  if (co2 <= 1000) {
    return Good;
  } else if (1000 < co2 && co2 <= 1400) {
    return Attention;
  } else if (1400 < co2 && co2 <= 2000) {
    return MoreAttention;
  } else {
    return Bad;
  }
}
