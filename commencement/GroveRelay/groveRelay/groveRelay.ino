
#include "Arduino.h"

#define controlBouton    3
// http://wiki.seeedstudio.com/Grove-Relay/
// https://www.seeedstudio.com/Grove-Relay.html
#define controlRelay    4

/*
 * Pour aller plus loin avec les relay
 * https://www.seeedstudio.com/blog/2020/01/03/arduino-tutorial-control-high-voltage-devices-with-relay-modules/
 */
boolean boutonEnfonce = false;

void setup() {
  // put your setup code here, to run once:

  pinMode(controlBouton, INPUT);
  pinMode(controlRelay, OUTPUT);
  /*
      Initiate the console output
  */
  Serial.begin(9600);
  Serial.println("Démarrage OK");
}


void loop() {
  // Si le bouton est enfoncé Et s'il ne l'était pas déjà
  if (leBoutonEstEnfonce() && leBoutonEtaitDejaEnfonce())
  {
      // Se rappeler que le bouton est appuyé
      commuteLeSouvenirDeLEtatDuBouton();
      Serial.println("Bouton appuyé");
      commuteLeRelay();
  }
  if (!leBoutonEstEnfonce() && !leBoutonEtaitDejaEnfonce())
  {
      commuteLeSouvenirDeLEtatDuBouton();
      Serial.println("Bouton relâché");
  }
}

void commuteLeSouvenirDeLEtatDuBouton() {
  boutonEnfonce = !boutonEnfonce;
}

boolean leBoutonEstEnfonce() {
  return digitalRead(controlBouton) == HIGH;
}

boolean leBoutonEtaitDejaEnfonce() {
  return boutonEnfonce == false;
}

void commuteLeRelay() {
    if(digitalRead(controlRelay) == HIGH){
      digitalWrite(controlRelay, LOW);
    } else {
      digitalWrite(controlRelay, HIGH);
    }
}
