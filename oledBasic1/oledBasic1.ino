

#include <Wire.h>
#include <SeeedOLED.h>
#include "Arduino.h"

char buffer[30];

void setup() {
  /* Initiate the Wire library and join the I2C bus as a master
    https://www.arduino.cc/en/reference/wire
  */
  Wire.begin();
  SeeedOled.init();
  SeeedOled.clearDisplay(); //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay(); //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode
  //Serial.begin(9600);
  //Serial.println("Starting up...");
  Serial.begin(9600);
  Serial.println("Tac o tac");

  displayHello();
}

void loop() {
  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  //displayHello();
}




void displayHello() {
  SeeedOled.setTextXY(0, 0);
  //for (int i = 0 ; i < 16 ; i++) {
  //  SeeedOled.putString("a");
  //}
  SeeedOled.putString("* ** B'jour ** *");
  SeeedOled.setTextXY(1, 0);
  SeeedOled.putString("Deuxième ligne");
  SeeedOled.setTextXY(2, 0);
  SeeedOled.putString("&é\"'(-è_çà)=");
  SeeedOled.setTextXY(3, 0);
  SeeedOled.putString("start watering");
  SeeedOled.setTextXY(4, 0);
  SeeedOled.putString("bluh");
  SeeedOled.setTextXY(5, 0);
  SeeedOled.putString("bluh");

  int n = sprintf(buffer, "salut");
  int padding = (16 - n) / 2;
  SeeedOled.setTextXY(6, padding);
  SeeedOled.putString(buffer);

  //sprintf(buffer, "%d.%d%% ", (int) (MoisHumidity),
  //        (int) ((int) (MoisHumidity * 100) % 100));
  n = sprintf(buffer, "%d.%d%% ", 2,
              (int) ((int) (2 * 100) % 100));
  padding = (16 - n) / 2;
  SeeedOled.setTextXY(7, padding);          //Set the cursor to Xth Page, Yth Column
  SeeedOled.putString(buffer);

}
