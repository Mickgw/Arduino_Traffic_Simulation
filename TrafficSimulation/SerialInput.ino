/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

char letter;
char incomingByte;
byte trafficLightValue;

int TYPE_OF_TRAFFICLIGHT[] = {
  1, //Netherlands
  2, //Germany
  3, //Austria
  4  //Warning lights
};

void readSerial() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read();
    if (incomingByte == 'D' || incomingByte == 'G' || incomingByte == 'A' || incomingByte == 'W') {
      letter = incomingByte;
    }
  }
}

byte switchTraffcLightValue() {
  switch (letter) {
    case 'D':
      trafficLightValue = TYPE_OF_TRAFFICLIGHT[0];
      break;
    case 'G':
      trafficLightValue = TYPE_OF_TRAFFICLIGHT[1];
      break;
    case 'A':
      trafficLightValue = TYPE_OF_TRAFFICLIGHT[2];
      break;
    case 'W':
      trafficLightValue = TYPE_OF_TRAFFICLIGHT[3];
      break;
    default:
      break;
  }
}

byte getTrafficLightValue() {
  return trafficLightValue;
}
