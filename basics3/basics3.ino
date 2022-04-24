
/*
   Programme qui affiche une page sur un écran LCD
   Un bouton permet d'incrémenter le numéro de page (0 quand max)


*/

// Arduino core
#include "Arduino.h"
// Pour utiliser le bus I²C
#include <Wire.h>
// Pour utiliser le OLED Display
#include <SeeedOLED.h>
// Pour le capteur de lumière
#include "SI114X.h"

char buffer[30];
int page = 0;

boolean leBouton2AEteClique;
#define buttonPin       2

SI114X SI1145 = SI114X();

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
  //Serial.begin(9600);
  //Serial.println("Tac o tac");

  /* Interrupt example
    https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  */
  pinMode(buttonPin, INPUT);
  leBouton2AEteClique = true;
  //attachInterrupt(digitalPinToInterrupt(buttonPin), display2, FALLING);

  Serial.begin(115200);
  Serial.println("Beginning Si1145!");
  /* Init UV */
  while (!SI1145.Begin()) {
    Serial.println("Si1145 is not ready!");
    delay(1000);
  }

  //displayHello();
  //display2();
}

void loop() {

  // Si le bouton est appuyé et que la condition n'a pas été visitée
  if (digitalRead(buttonPin) == 1 && leBouton2AEteClique == false) {
    incrementerPage();
    leBouton2AEteClique = true;
    // Si le bouton est relâché et que la condition a été visitée
  } else if (digitalRead(buttonPin) == 0 && leBouton2AEteClique == true) {
    displayPage();
    leBouton2AEteClique = false;
  }
}

/***********************************************************************************
 * *********************************************************************************
   GESTION DE L'AFFICHAGE DES PAGES
   *********************************************************************************
   *********************************************************************************
*/
void displayPage() {
  if (leBouton2AEteClique) {
    toutEffacer();
    switch (page) {
      case 0:
        page0();
        break;
      case 1:
        page1();
        break;
      case 2:
        page2();
        break;
      case 3:
        page3();
        break;
      case 4:
        page4();
        break;
      case 5:
        page5();
        break;
      case 6:
        page6();
        break;
      case 7:
        page7();
        break;
      default: break;
    }
  }
}

void page0() {

  float UVIndex = (float) SI1145.ReadUV() / 100 + 0.5;
  int bufferSize = sprintf(buffer, "%d", (float) UVIndex);
  int padding = (16 - bufferSize) / 2;
  SeeedOled.setTextXY(0, padding);
  SeeedOled.putString(buffer);

  UVIndex = (float) SI1145.ReadIR() / 100 + 0.5;
  bufferSize = sprintf(buffer, "%d", (float) UVIndex);
  padding = (16 - bufferSize) / 2;
  SeeedOled.setTextXY(1, padding);
  SeeedOled.putString(buffer);

  UVIndex = (float) SI1145.ReadVisible() / 100 + 0.5;
  bufferSize = sprintf(buffer, "%d", (float) UVIndex);
  padding = (16 - bufferSize) / 2;
  SeeedOled.setTextXY(2, padding);
  SeeedOled.putString(buffer);

  bufferSize = sprintf(buffer, "Page 0");
  padding = (16 - bufferSize) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void page1() {
  int bufferSize = sprintf(buffer, "Page 1");
  int padding = (16 - bufferSize) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void page2() {
  int bufferSize = sprintf(buffer, "Page 2 ff");
  int padding = (16 - bufferSize) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void page3() {
  int n = sprintf(buffer, "Page 3");
  int padding = (16 - n) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void page4() {
  int n = sprintf(buffer, "Page 4");
  int padding = (16 - n) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void page5() {
  int n = sprintf(buffer, "Page 5");
  int padding = (16 - n) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void page6() {
  int n = sprintf(buffer, "Page 6");
  int padding = (16 - n) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void page7() {
  int n = sprintf(buffer, "Page 7");
  int padding = (16 - n) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);
}

void incrementerPage() {
  page++;
  if (page > 7 ) {
    page = 0;
  }
}

void displayHello() {
  toutEffacer();

  SeeedOled.setTextXY(1, 0);
  sprintf(buffer, "%d ", (int) millis());
  SeeedOled.putString(buffer);


  int n = sprintf(buffer, "Bonjour");
  int padding = (16 - n) / 2;
  SeeedOled.setTextXY(6, padding);
  SeeedOled.putString(buffer);

  n = sprintf(buffer, "%d.%d%% ", 2,
              (int) ((int) (2 * 100) % 100));
  padding = (16 - n) / 2;
  SeeedOled.setTextXY(7, padding);
  SeeedOled.putString(buffer);

}

void toutEffacer() {
  for (int i = 0 ; i < 8; i++) {
    effacerLigne(i);
  }
}

void effacerLigne(int ligne) {
  SeeedOled.setTextXY(ligne, 0);
  for (int i = 0 ; i < 16 ; i++) {
    SeeedOled.putString(" ");
  }
}

void display2(int page) {
  SeeedOled.setTextXY(0, 0);
  //for (int i = 0 ; i < 16 ; i++) {
  sprintf(buffer, "%d ", page);
  SeeedOled.putString(buffer);
  //}
  SeeedOled.setTextXY(1, 0);
  for (int i = 0 ; i < 16 ; i++) {
    SeeedOled.putString("b");
  }
  SeeedOled.setTextXY(2, 0);
  for (int i = 0 ; i < 16 ; i++) {
    SeeedOled.putString("c");
  }
  SeeedOled.setTextXY(3, 0);
  for (int i = 0 ; i < 16 ; i++) {
    SeeedOled.putString("d");
  }
  SeeedOled.setTextXY(4, 0);
  for (int i = 0 ; i < 16 ; i++) {
    SeeedOled.putString("e");
  }
  SeeedOled.setTextXY(5, 0);
  for (int i = 0 ; i < 16 ; i++) {
    SeeedOled.putString("f");
  }

  effacerLigne(6);
  effacerLigne(7);
}



/***********************************************************************************
 * *********************************************************************************
   GESTION DE L'AFFICHAGE DU BOUTON PIN 2
   *********************************************************************************
   *********************************************************************************
*/


void ButtonClick() {

  //if (digitalRead(ButtonPin) == 0) {
  //delay(10);
  //if (digitalRead(ButtonPin) == 0) {
  //ButtonFlag = 1;
  SeeedOled.clearDisplay();
  //}
  //}
}
