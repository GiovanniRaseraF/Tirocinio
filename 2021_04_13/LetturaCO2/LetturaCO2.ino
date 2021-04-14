#include "SCD30.h"
#include <Wire.h>

void setup() {
  // put your setup code here, to run once:
  Wire.begin();
  Serial.begin(115200);
  Serial.println("SCD30 Raw Data");
  scd30.initialize();
}

void loop() {
  // put your main code here, to run repeatedly:
   float result[3] = {0};

    if (scd30.isAvailable()) {
      //Serial.println("Available");
        scd30.getCarbonDioxideConcentration(result);
        Serial.print("Carbon Dioxide Concentration is: ");
        Serial.print(result[0]);
        Serial.println(" ppm");
        Serial.println(" ");
        Serial.print("Temperature = ");
        Serial.print(result[1]);
        Serial.println(" ℃");
        Serial.println(" ");
        Serial.print("Humidity = ");
        Serial.print(result[2]);
        Serial.println(" %");
        Serial.println(" ");
        Serial.println(" ");
        Serial.println(" ");
    }

    delay(3000);

}
