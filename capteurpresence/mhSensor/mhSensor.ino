
#include "Arduino.h"

/*
 * Références :
 *  - https://www.electronicshub.org/interfacing-voltage-sensor-with-arduino/
*/

int A0Pin = 0;
float  A0Val = 0; 
float  A0LastVal = 0;
float  offset = 3;

void setup() {
    Serial.begin(9600);
}

void loop() {
    A0Val = analogRead(A0Pin);
    if(A0Val < A0LastVal - offset || A0Val > A0LastVal + offset){
      A0LastVal = A0Val;
      Serial.println(A0Val / 40);
      delay(50);
    }
}
