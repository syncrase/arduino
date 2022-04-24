
/*
   Programme qui affiche une page sur un écran LCD
   Un bouton permet d'incrémenter le numéro de page (0 quand max)
   Un capteur de luminosité
   Un capteur de température humidité de l'air
   Un capteur d'humidité du sol
   Un capteur de débit d'eau
*/

#include "Arduino.h"
// Permet de joindre le bus I²C
#include <Wire.h>
// Permet d'utiliser le OLED Display, branché sur un port I²C
#include <SeeedOLED.h>
// Capteur de luminosité, branché sur un port I²C
#include "SI114X.h"
// Capteur humidité et de température de l'air
#include "DHT.h"
// Encoder
#include <Encoder.h>
#include <TimerOne.h>


// http://wiki.seeedstudio.com/Grove-Sunlight_Sensor/
SI114X SI1145 = SI114X();

// https://www.arduinolibraries.info/libraries/dht-sensor-library
// Branché sur A0
#define DHTPIN  A0
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

// Capteur d'humidité du sol
// http://wiki.seeedstudio.com/Grove-Moisture_Sensor/
// Branché sur A1
#define moisturePin     A1

// Capteur de débit d'eau
// http://wiki.seeedstudio.com/M11_1.25_Water_flow_Sensor/
// https://www.seeedstudio.com/M11-1-25-Water-Flow-Sensor-p-1345.html
// Branché sur D5
#define waterflowPin    5
unsigned int waterflowFlag =  0;
unsigned int edgePerSec = 0;  // count the edges
#define oneSecond       1000
unsigned long startTime = 0;

// Bouton pressoir
// Branché sur D2
#define buttonPin       2
char buffer[16];
int page = 0;
boolean leBouton2AEteClique;

// Encoder
// Branché sur D3 (qui utilise aussi D4)
#define encoderPin1     3
#define encoderPin2     4

void setup() {
  /* Initiate the Wire library and join the I2C bus as a master
    https://www.arduino.cc/en/reference/wire
  */
  Wire.begin();
  /*
      Initiate the OLED Display
  */
  SeeedOled.init();
  SeeedOled.clearDisplay(); //clear the screen and set start position to top left corner
  SeeedOled.setNormalDisplay(); //Set display to normal mode (i.e non-inverse mode)
  SeeedOled.setPageMode();           //Set addressing mode to Page Mode

  /*
      Initiate the console output
  */
  Serial.begin(9600);
  Serial.println("Starting up...");

  /* Interrupt example
    https://www.arduino.cc/reference/en/language/functions/external-interrupts/attachinterrupt/
  */
  pinMode(buttonPin, INPUT);
  leBouton2AEteClique = true;
  //attachInterrupt(digitalPinToInterrupt(buttonPin), display2, FALLING);

  /*
      Initiate the luminosity sensor
  */
  while (!SI1145.Begin()) {
    Serial.println("Si1145 is not ready!");
    delay(1000);
  }

  /*
      Initiate the DHT humidity/temperature sensors
  */
  dht.begin();

  /* Init Water flow */
  pinMode(waterflowPin, INPUT);

  /* Init Encoder */
  pinMode(encoderPin1, INPUT);
  pinMode(encoderPin2, INPUT);
  encoder.Timer_init();
}

void loop() {

  // Si le bouton est appuyé et que la condition n'a pas été visitée
  if (digitalRead(buttonPin) == 1 && leBouton2AEteClique == false) {
    incrementerPage();
    leBouton2AEteClique = true;
    // Si le bouton est relâché et que la condition a été visitée
  } else if (digitalRead(buttonPin) == 0 ) {
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
  switch (page) {
    case 0:
      lumiere();
      break;
    case 1:
      temperature();
      break;
    case 2:
      humidite();
      break;
    case 3:
      encoderLogic();
      break;
    case 4:
      debit();
      break;
    default: break;
  }
}

void lumiere() {
  int length = sprintf(buffer, "Lumiere");
  afficher(0, length);

  // parceque sprintf(buffer, "UV : %f", 0.03); ne fonctionne pas
  char value[5];
  dtostrf((float)SI1145.ReadUV() / 100, 5, 2, value);
  afficher(1, "UV : %s", value);

  afficher(2, "IR : %d", SI1145.ReadIR());
  afficher(3, "Visible : %d", SI1145.ReadVisible());

  length = sprintf(buffer, "Page 0");
  afficher(7, length);
}

void temperature() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // check if returns are valid, if they are NaN (not a number) then something went wrong!
  if (isnan(t) || isnan(h))
  {
    Serial.println("Failed to read from DHT");
  }

  //effacerLigne(0);
  int length = sprintf(buffer, "Temperature");
  afficher(0, length);

  char value[8];
  dtostrf(t, 5, 2, value);
  afficher(1, "Temp. : %s", value);

  dtostrf(h, 5, 2, value);
  afficher(2, "Humi. : %s", value);

  length = sprintf(buffer, "Page 1");
  afficher(7, length);
}

void humidite() {
  int length;
  length = sprintf(buffer, "Humidite");
  afficher(0, length);

  // Conversion du decimal en string
  char value[3];
  dtostrf(analogRead(moisturePin), 3, 0, value);
  afficher(3, "Humi. : %s", value);

  length = sprintf(buffer, "Page 2");
  afficher(7, length);
}

void encoderLogic() {

  // TODO ne fonctionne pas vraiment, encoderPin1 et pin2 retournent toujours 1. Et indistinctement 0 quand on tourne dans un sens ou l'autre
  // Interrupts are useful for making things happen automatically in microcontroller programs and can help solve timing problems.
  // Good tasks for using an interrupt may include reading a rotary encoder, or monitoring user input.
  // http://wiki.seeedstudio.com/Grove-Encoder/

  int length;

  length = sprintf(buffer, "Encoder");
  afficher(0, length);

  char value[3];
  int encoderPos = digitalRead(encoderPin1);
  dtostrf(encoderPos, 3, 0, value);
  afficher(2, "Encoder1 : %s", value);

  dtostrf(digitalRead(encoderPin2), 3, 0, value);
  afficher(3, "Encoder2 : %s", value);

  //if (encoderPos == HIGH) {
  //  length = sprintf(buffer, "HIGH");
  //} else if (encoderPos == LOW) {
  //  length = sprintf(buffer, "LOW");
  //} else {
  //  length = sprintf(buffer, "UNKNOWN");
  //}
  //length = sprintf(buffer, displayedString);

  encoderPos = encoder.rotate_flag;
  dtostrf(encoderPos, 3, 0, value);
  length = sprintf(buffer, "Rotate : %s", value);
  if (encoder.rotate_flag == 1)
  {
    if (encoder.direct == 1)
    {
      length = sprintf(buffer, "direct 1");
    }
    else
    {
      //length = sprintf(buffer, "direct 0");
    }
    encoder.rotate_flag = 0;
  } else {
    ///length = sprintf(buffer, "no rotation");
  }

  afficher(5, length);

  length = sprintf(buffer, "Page 3");
  afficher(7, length);
}

void debit() {
  int length;

  length = sprintf(buffer, "Debit");
  afficher(0, length);

  char value[3];
  dtostrf(digitalRead(waterflowPin), 3, 0, value);
  afficher(2, "Debit : %s", value);

  if (startTime == 0) {
    startTime = millis();
  }

  // Incrément à chaque changement d'état
  if (digitalRead(waterflowPin) == 1 && waterflowFlag == 0) {
    waterflowFlag = 1;
    edgePerSec++;
  } else if (digitalRead(waterflowPin) == 0 && waterflowFlag == 1) {
    waterflowFlag = 0;
    edgePerSec++;
  }

  if ((millis() - startTime) > oneSecond) {
    dtostrf(edgePerSec, 3, 0, value);
    afficher(3, "Par sec. : %s", value);
    edgePerSec = 0;
    startTime = millis();
  }


  length = sprintf(buffer, "Page 4");
  afficher(7, length);
}

void afficher(int line, const char* string, const char* value) {
  int lineLength = sprintf(buffer, string, value);
  afficher(line, lineLength);
}

void afficher(int line, int lineLength) {
  int padding = (16 - lineLength) / 2;
  SeeedOled.setTextXY(line, padding);
  SeeedOled.putString(buffer);
}

void displayHello() {

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

void incrementerPage() {
  toutEffacer();
  page++;
  if (page > 4 ) {
    page = 0;
  }
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
