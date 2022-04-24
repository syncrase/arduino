
#include "Arduino.h"

// Encoder
#include <Encoder.h>
#include <TimerOne.h>

#define encoderPin4     4
#define encoderPin5     5

#define ledPin2     2
#define buzzerPin3     3

char buffer[60];
  
int pin4ValuePrecedent;
int pin5ValuePrecedent;

boolean receptionDeLaSequenceEnCours = false;
boolean auRepos = true;

void setup() {
  Serial.begin(9600);
  Serial.println("Démarrage en cours");
  encoder.Timer_init();
  pin4ValuePrecedent = HIGH;
  pin5ValuePrecedent = HIGH;
  Serial.println("Démarrage OK");
}

void loop() {

  int encoderPin4Value = digitalRead(encoderPin4);
  int encoderPin5Value = digitalRead(encoderPin5);

  boolean sautALaLigne = false;


  
  // séquence horaire     (HIGH, HIGH) -> (HIGH, LOW) -> (LOW, LOW) -> (LOW, HIGH) -> (HIGH, HIGH)
  // séquence antihoraire (HIGH, HIGH) -> (LOW, HIGH) -> (LOW, LOW) -> (HIGH, LOW) -> (HIGH, HIGH)
testDesDifferentesCombinaisonsDesDeuxPins(encoderPin4Value, encoderPin5Value);



  
}


void testDesDifferentesCombinaisonsDesDeuxPins(int encoderPin4Value, int encoderPin5Value){
  
  boolean sautALaLigne = false;
  
  /*
 * Les 2 pins sont commutées
 */
  // Si les pins 4 et 5 ont été commutées (LOW, HIGH) -> (HIGH, LOW)
  if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == HIGH && encoderPin4Value == HIGH && encoderPin5Value == LOW) {
    sprintf(buffer, "(LOW, HIGH) -> (HIGH, LOW)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = HIGH;
    pin5ValuePrecedent = LOW;
    sautALaLigne = true;
  } 
  
  // Si les pins 4 et 5 ont été commutées (HIGH, LOW) -> (LOW, HIGH)
  if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == LOW && encoderPin4Value == LOW && encoderPin5Value == HIGH) {
    sprintf(buffer, "(HIGH, LOW) -> (LOW, HIGH)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = LOW;
    pin5ValuePrecedent = HIGH;
    sautALaLigne = true;
  } 
  
  // Si les pins 4 et 5 ont été commutées (LOW, LOW) -> (HIGH, HIGH)
  if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == LOW && encoderPin4Value == HIGH && encoderPin5Value == HIGH) {
    sprintf(buffer, "(LOW, LOW) -> (HIGH, HIGH)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = HIGH;
    pin5ValuePrecedent = HIGH;
    sautALaLigne = true;
  } 
  
  // Si les pins 4 et 5 ont été commutées (HIGH, HIGH) -> (LOW, LOW)
  if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == HIGH && encoderPin4Value == LOW && encoderPin5Value == LOW) {
    sprintf(buffer, "(HIGH, HIGH) -> (LOW, LOW)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = LOW;
    pin5ValuePrecedent = LOW;
    sautALaLigne = true;
  } 

  /*
   * La pin 4 commute avec la 5 constante
   */
  // Si la pin 4 a été commutée en HIGH avec la 5 qui reste à LOW (LOW, LOW) -> (HIGH, LOW)
  if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == LOW && encoderPin4Value == HIGH && encoderPin5Value == LOW) {
    sprintf(buffer, "(LOW, LOW) -> (HIGH, LOW)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = HIGH;
    pin5ValuePrecedent = LOW;
    sautALaLigne = true;
  } 
  // Si la pin 4 a été commutée en HIGH avec la 5 qui reste à HIGH (LOW, HIGH) -> (HIGH, HIGH)
  if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == HIGH && encoderPin4Value == HIGH && encoderPin5Value == HIGH) {
    sprintf(buffer, "(LOW, HIGH) -> (HIGH, HIGH)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = HIGH;
    pin5ValuePrecedent = HIGH;
    sautALaLigne = true;
  } 
  
  // Si la pin 4 a été commutée en LOW avec la 5 qui reste à LOW (HIGH, LOW) -> (LOW, LOW)
  if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == LOW && encoderPin4Value == LOW && encoderPin5Value == LOW) {
    sprintf(buffer, "(HIGH, LOW) -> (LOW, LOW)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = LOW;
    pin5ValuePrecedent = LOW;
    sautALaLigne = true;
  } 
  
  // Si la pin 4 a été commutée en LOW avec la 5 qui reste à HIGH (HIGH, HIGH) -> (LOW, HIGH)
  if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == HIGH && encoderPin4Value == LOW && encoderPin5Value == HIGH) {
    sprintf(buffer, "(HIGH, HIGH) -> (LOW, HIGH)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = LOW;
    pin5ValuePrecedent = HIGH;
    sautALaLigne = true;
  } 

  /*
   * La pin 5 commute avec la 4 constante
   */
  // Si la pin 5 a été commutée en HIGH avec la 4 qui reste à LOW (LOW, LOW) -> (LOW, HIGH)
  if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == LOW && encoderPin4Value == LOW && encoderPin5Value == HIGH) {
    sprintf(buffer, "(LOW, LOW) -> (LOW, HIGH)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = LOW;
    pin5ValuePrecedent = HIGH;
    sautALaLigne = true;
  } 
  // Si la pin 5 a été commutée en LOW avec la 4 qui reste à LOW (LOW, HIGH) -> (LOW, LOW)
  if (pin4ValuePrecedent == LOW && pin5ValuePrecedent == HIGH && encoderPin4Value == LOW && encoderPin5Value == LOW) {
    sprintf(buffer, "(LOW, HIGH) -> (LOW, LOW)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = LOW;
    pin5ValuePrecedent = LOW;
    sautALaLigne = true;
  } 
  // Si la pin 5 a été commutée en LOW avec la 4 qui reste à HIGH (HIGH, HIGH) -> (HIGH, LOW)
  if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == HIGH && encoderPin4Value == HIGH && encoderPin5Value == LOW) {
    sprintf(buffer, "(HIGH, HIGH) -> (HIGH, LOW)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = HIGH;
    pin5ValuePrecedent = LOW;
    sautALaLigne = true;
  } 
  // Si la pin 5 a été commutée en HIGH avec la 4 qui reste à HIGH (HIGH, LOW) -> (HIGH, HIGH)
  if (pin4ValuePrecedent == HIGH && pin5ValuePrecedent == LOW && encoderPin4Value == HIGH && encoderPin5Value == HIGH) {
    sprintf(buffer, "(HIGH, LOW) -> (HIGH, HIGH)");
    Serial.write(buffer);
    Serial.println();
    pin4ValuePrecedent = HIGH;
    pin5ValuePrecedent = HIGH;
    sautALaLigne = true;
  } 
}
