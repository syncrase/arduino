


#include "Arduino.h"

int A0Pin = 0; // digital
float A0Val = 0; //
float A0LastVal = 0; //

void setup() {
  Serial.begin(9600);
}

void loop() {

  /*
     5V : 1019 Tension max -> tension d'alimentation
     4V : 814
     3V : 609
     2V : 404
     1V : 201
     0.5V : 99
  */
  A0Val = analogRead(A0Pin);
  if (A0Val < (A0LastVal - 3) || A0Val > (A0LastVal + 3)) {
    Serial.print(A0Val / 203);
    Serial.println(" V");
    A0LastVal = A0Val;
  }
}
