/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

int displayCountdown[] = {
  B10111110, //digit 6
  B10110110, //digit 5
  B01100110, //digit 4
  B11110010, //digit 3
  B11011010, //digit 2
  B01100000, //digit 1
  B11111100  //digit 0
};

const int DISPLAY_PINS2[] = {
  2, //CLOCKPIN
  3, //LATCHPIN
  4  //DATAPIN
};

const byte DISPLAY_STOP = B10110110;
const byte DISPLAY_WALK = B00011100;
const byte DISPLAY_TEST = B11111111;
const byte DISPLAY_NOTHING = B00000000;

static int displayPattern;
const int NORMAL_INTERVAL = 1000;
unsigned long int previousMillisDisplay;

void displaySetup() {
  pinMode(DISPLAY_PINS2[2], OUTPUT);
  pinMode(DISPLAY_PINS2[1], OUTPUT);
  pinMode(DISPLAY_PINS2[0], OUTPUT);
}

byte setDisplayPatternCountdown() {
  unsigned long currentMillisCountdown = millis();
  static int arrayIndex = 0;

  if (currentMillisCountdown - previousMillisDisplay >= NORMAL_INTERVAL) {
    previousMillisDisplay = currentMillisCountdown;

    //If time passed do this function and up the arrayIndex with 1
    displayPattern = displayCountdown[arrayIndex];
    arrayIndex++;

    //When it goes "out of bounds" put the array index back to 0
    if (arrayIndex > 6) {
      arrayIndex = 0;
    }
  }
}

byte displaySigns(char key) {
  switch (key) {
    //L for Lopen
    case 'L':
      displayPattern = DISPLAY_WALK;
      break;
    //S for Stop
    case 'S':
      displayPattern = DISPLAY_STOP;
      break;
    //T for Test
    case 'T':
      displayPattern = DISPLAY_TEST;
      break;
    //N for Nothing
    case 'N':
      displayPattern = DISPLAY_NOTHING;
      break;
  }
}

byte getDisplayBytes() {
  return displayPattern;
}
