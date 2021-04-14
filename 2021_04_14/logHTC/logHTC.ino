#include "SCD30.h"
#include <Wire.h>
#define RED 3                  
#define GREEN 2

#define Good 0
#define Attention 1
#define MoreAttention 2
#define Bad 3

long timeDelay = 1000;

long prevTime = 0, newTime = 0;
int cicles = 0;
int states = 0;
float temperature = 0, humidity = 0, co2 = 0;
float resultHTC[3] = {0};

/* Danger levels            Color               Min     Max
// Good                     Green               Below   1000
// Attention                Yellow              1000    1400
// More attention           Yellow blinking     1400    2000
// Bad                      Red    blinking     2000    Above*/

int selectState(float co2){
  if(co2 <= 1000){
    return Good;
  }else if(1000 < co2 && co2 <= 1400){
    return Attention;
  }else if(1400 < co2 && co2 <= 2000){
    return MoreAttention;
  }else{
    return Bad;
  }
}

void blinkDangerLed(int state){
  switch(state){
    case Good:
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      delay(timeDelay);
    break;
    case Attention:
      digitalWrite(RED, LOW);
      for(int i = 0; i < timeDelay / 1000; i++){  
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
      for(int i = 0; i < timeDelay/100; i++){  
        digitalWrite(RED, HIGH);
        delay(timeDelay / (timeDelay/100));
        digitalWrite(RED, LOW);
        delay(timeDelay / (timeDelay/100));
      }
    break;
  }
}

void setup() {
    Wire.begin();
    Serial.begin(9600);
    pinMode(RED, OUTPUT);
    pinMode(GREEN, OUTPUT);
    digitalWrite(RED, LOW);
    digitalWrite(GREEN, LOW);
    scd30.initialize();
    scd30.setAutoSelfCalibration(1);
}


void loop() {
    newTime = millis();
    if (scd30.isAvailable()) {
        scd30.getCarbonDioxideConcentration(resultHTC);
        co2           += resultHTC[0];
        temperature   += resultHTC[1];
        humidity      += resultHTC[2];
        cicles++;
        
        if(newTime - prevTime > 60000){
          Serial.print(co2/(float)cicles); Serial.print(",");
          Serial.print(temperature/(float)cicles); Serial.print(",");
          Serial.print(humidity/(float)cicles); Serial.print("");
          Serial.println("");
          
          temperature = 0;
          humidity = 0; 
          co2 = 0;
          cicles = 0;
          
          prevTime = newTime;
        }
    }

    states = selectState(resultHTC[0]);
    blinkDangerLed(states);
}
