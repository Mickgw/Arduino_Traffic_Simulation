/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

const int NR_OUTPUT_PINS = 16;

const int DISPLAY_PINS[] = {
  2, //CLOCKPIN
  3, //LATCHPIN
  4  //DATAPIN
};

void sendToShiftRegisters() {
  digitalWrite(DISPLAY_PINS[1], LOW);

  for (int pin = 0; pin < NR_OUTPUT_PINS; pin++) {
    byte toDisplay = pin < 8 ? getLedPattern() : getDisplayBytes();

    int bitNr = pin < 8 ? pin : pin - 8;

    digitalWrite(DISPLAY_PINS[0], LOW);

    if (checkIfZeroOrOne(toDisplay, bitNr)) {
      digitalWrite(DISPLAY_PINS[2], HIGH);
    } else {
      digitalWrite(DISPLAY_PINS[2], LOW);
    }
    digitalWrite(DISPLAY_PINS[0], HIGH);
  }
  digitalWrite(DISPLAY_PINS[1], HIGH);
}


boolean checkIfZeroOrOne(byte pattern, byte bitNr) {
  byte bytePattern = B00000001;

  if ((pattern & (bytePattern << bitNr)) == 0 ) {
    return false;
  } else {
    return true;
  }
}
