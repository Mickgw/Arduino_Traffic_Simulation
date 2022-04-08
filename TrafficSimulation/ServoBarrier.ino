/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

#include <Servo.h>
Servo servo;

const int SERVOPIN = 9;
unsigned long previousMillisBarrierClosing;
unsigned long previousMillisBarrierOpening;

byte barrierOpen = 180;
byte barrierClosed = 0;
byte servoSpeed = 75;

void servoSetup() {
  servo.attach(SERVOPIN);
}

void doBarrierTask(char barrierTask) {
  //O = Open en C = Close
  switch (barrierTask) {
    case 'O':
      openBarrier();
      break;
    case 'C':
      closeBarrier();
      break;
    default:
      //nothing
      break;
  }
}

void openBarrier() {
  unsigned long currentMillisBarrierOpening = millis();

  if (currentMillisBarrierOpening - previousMillisBarrierOpening >= servoSpeed) {
    previousMillisBarrierOpening = currentMillisBarrierOpening;

    for (int angle = 0; angle <= barrierOpen; angle++) {
      Serial.println((String) " Slagboom gaat open! De angle van de slagboom = " + angle);
      servo.write(angle);
      if (angle == barrierOpen) {
        break; //Zodra de angle even groot is als de
      }
    }
  }
}

void closeBarrier() {
  unsigned long currentMillisBarrierClosing = millis();

  if (currentMillisBarrierClosing - previousMillisBarrierClosing >= servoSpeed) {
    previousMillisBarrierClosing = currentMillisBarrierClosing;

    for (int angle = barrierOpen; angle >= barrierClosed; angle--) {
      Serial.println((String) " Slagboom gaat dicht! De angle van de slagboom = " + angle);
      servo.write(angle);
      if (angle == barrierClosed) {
        break;
      }
    }
  }
}

byte getServoReadValue() {
  return servo.read();
}

boolean isBarrierOpen() {
  boolean isBarrierOpen;

  if (getServoReadValue() == barrierOpen) {
    isBarrierOpen = true;
  } else {
    isBarrierOpen = false;
  }
  return isBarrierOpen;
}
