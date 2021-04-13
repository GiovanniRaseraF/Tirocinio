#include "SCD30.h"
#include <Wire.h>
#define RED 22                    
#define BLUE 24            
#define GREEN 23      


/* Danger levels            Color               Min     Max
// Good                     Green               Below   1000
// Attention                Yellow              1000    1400
// More attention           Yellow blinking     1400    2000
// Bad                      Red    blinking     2000    Above*/
void blinkDangerLed(float co2){
  if(co2 <= 1000){
    digitalWrite(BLUE, HIGH);
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, LOW);
  }else if(1000 < co2 && co2 <= 1400){
    digitalWrite(BLUE, LOW);
    digitalWrite(RED, HIGH);
    digitalWrite(GREEN, HIGH);
  }else if(1400 < co2 && co2 <= 2000){
    for(int i = 0; i < 5; i++){
      digitalWrite(BLUE, LOW);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      delay(100);
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      delay(100);
    }
  }else{
    for(int i = 0; i < 5; i++){
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, LOW);
      digitalWrite(GREEN, HIGH);
      delay(100);
      digitalWrite(BLUE, HIGH);
      digitalWrite(RED, HIGH);
      digitalWrite(GREEN, HIGH);
      delay(100);
    }
  }
}

void setup() {
    Wire.begin();
    Serial.begin(9600);
    scd30.initialize();
    scd30.setAutoSelfCalibration(0);
}



void loop() {
    float resultHTC[3] = {0};
    float temperature = 0, humidity = 0, co2 = 0;
    
    if (scd30.isAvailable()) {
        scd30.getCarbonDioxideConcentration(resultHTC);
        co2           = resultHTC[0];
        temperature   = resultHTC[1];
        humidity      = resultHTC[2];

        //if(millis() % 2000 == 0){
          Serial.print(co2); Serial.print(",");
          Serial.print(temperature); Serial.print(",");
          Serial.print(temperature); Serial.print("");
          Serial.println("");
        //}
    }

    blinkDangerLed(co2);
    delay(1000);
}
