
#include "Arduino.h"

// Encoder
#include <Encoder.h>
#include <TimerOne.h>

#define encoderPin4     4
#define encoderPin5     5

#define ledPin2     2
#define buzzerPin3     3

char buffer[30];
  
int pin4ValuePrecedent;
int pin5ValuePrecedent;

boolean sequenceEncoursDeTraitement = false;
boolean sequenceHoraire = false;
boolean sequenceAntiHoraire = false;

int compteur = 0;
boolean receptionDeLaSequenceEnCours = false;

void setup() {
  Serial.begin(9600);
  Serial.println("Démarrage en cours");
  
  pinMode(ledPin2, OUTPUT);
  pinMode(buzzerPin3, OUTPUT);
  
  encoder.Timer_init();

  pin4ValuePrecedent = HIGH;
  pin5ValuePrecedent = HIGH;
  Serial.println("Démarrage OK");
}

void loop() {

  int encoderPin4Value = digitalRead(encoderPin4);
  int encoderPin5Value = digitalRead(encoderPin5);


  if(receptionDeLaSequenceEnCours == true){
        sprintf(buffer, "Début d'itération");
        Serial.write(buffer);
        Serial.println();
        sprintf(buffer, "Nouvelles valeurs : (%d ; %d)", encoderPin4Value, encoderPin5Value);
        Serial.write(buffer);
        Serial.println();
  }
  
  //if (sequenceHoraire == false){
    // séquence antihoraire (pin4, pin5) : (HIGH, HIGH) -> (LOW, HIGH) -> (LOW, LOW) -> (HIGH, LOW) -> (HIGH, HIGH)
    if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == HIGH && encoderPin4Value == LOW && encoderPin5Value == HIGH) {
        sprintf(buffer, "Séquence anti-horaire 1");
        Serial.write(buffer);
        Serial.println();
      pin4ValuePrecedent = LOW;
      pin5ValuePrecedent = HIGH;
      sequenceAntiHoraire = true;
      receptionDeLaSequenceEnCours = true;
    } else if(sequenceAntiHoraire == true){
        
      if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == HIGH && encoderPin4Value == LOW && encoderPin5Value == LOW) {
        sprintf(buffer, "Séquence anti-horaire 2");
        Serial.write(buffer);
        Serial.println();
        pin4ValuePrecedent = LOW;
        pin5ValuePrecedent = LOW;
      } else if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == LOW && encoderPin4Value == HIGH && encoderPin5Value == LOW) {
        sprintf(buffer, "Séquence anti-horaire 3");
        Serial.write(buffer);
        Serial.println();
        pin4ValuePrecedent = HIGH;
        pin5ValuePrecedent = LOW;
      } else if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == LOW && encoderPin4Value == HIGH && encoderPin5Value == HIGH) {
        sprintf(buffer, "Séquence anti-horaire valide");
        Serial.write(buffer);
        Serial.println();
        sequenceAntiHoraire = false;
        receptionDeLaSequenceEnCours = false;
        digitalWrite(ledPin2, HIGH);
        //digitalWrite(buzzerPin3, HIGH);
        pin4ValuePrecedent = HIGH;
        pin5ValuePrecedent = HIGH;
      } else {
        sprintf(buffer, "Séquence anti-horaire invalide");
        Serial.write(buffer);
        sprintf(buffer, "(%d ; %d) -> (%d ; %d)", pin4ValuePrecedent, pin5ValuePrecedent, encoderPin4Value, encoderPin5Value);
        Serial.write(buffer);
        Serial.println();
        sequenceAntiHoraire = false;
        receptionDeLaSequenceEnCours = false;
        pin4ValuePrecedent = HIGH;
        pin5ValuePrecedent = HIGH;
      }
    }
  //}

  if(receptionDeLaSequenceEnCours == true){
        sprintf(buffer, "Traitement en cours, fin d'itération");
        Serial.write(buffer);
        Serial.println();
        sprintf(buffer, "Valeurs sauvegardées : (%d ; %d)", pin4ValuePrecedent, pin5ValuePrecedent);
        Serial.write(buffer);
        Serial.println();
        Serial.println();
  }
  
}
