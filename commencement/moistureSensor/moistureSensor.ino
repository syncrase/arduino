
// Arduino core
#include "Arduino.h"
// Permet de joindre le bus I²C
#include <Wire.h>

// Capteur d'humidité du sol
// http://wiki.seeedstudio.com/Grove-Moisture_Sensor/
// Branché sur A1
#define moisturePin     A1
char buffer[16];

void setup() {
  // 2000 n'affiche que des points d'interrogations à l'envers !
  // 3000 n'affiche que des points d'interrogations à l'envers et des carrés qui vont vites!
  // 4000 n'affiche que des points d'interrogations à l'envers et des carrés qui vont très vites!
  Serial.begin(1200);
}

void loop() {
  
  sprintf(buffer, "Humidite");
  // Conversion du decimal en string
  char value[3];
  dtostrf(analogRead(moisturePin), 3, 0, value);
  Serial.write(value);
  Serial.println();
  delay(100);
}
