/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

static byte ledPattern;

unsigned long currentTimeDutch, currentTimeGerman, currentTimeAustrian, currentTimeOrangeBlinking, currentTimeTestLights;
unsigned long startTimeDutch, startTimeGerman, startTimeAustrian, startTimeOrangeBlink, startTimeTestLights;
unsigned long previousMillisLeftBlinkingGreen, previousMillisRightBlinkingGreen, previousMillisTestingLights;

boolean startTimerDutchTrafficLights, startTimerGermanTrafficLights, startTimerAustrianTrafficLights, startTimerBlinkingOrange, startTimerTestLights = false;

const int BOTH_TRAFFICLIGHTS_RED = B00100100;
const int BOTH_TRAFFICLIGHTS_ORANGE = B01001000;

const int ALL_LEFT_TRAFFICLIGHTS_OFF = B00000100;
const int ALL_RIGHT_TRAFFICLIGHTS_OFF = B00100000;
const int ALL_TRAFFICLIGHTS_OFF = B00000000;
const int ALL_TRAFFICLIGHTS_ON = B11111111;

const int TRAFFICLIGHTDURATIONS[] = {
  5000, //Green light duration
  2500, //Orange light duration
  3000, //Red and orange light duration at the same time
  3000, //Green light blink period duration
  500,  //Blinking trafficlight duration
  1000, //Blinking trafficlight period
  1000  //Led duration for testing
};

const int TEST_ALL_LIGHTS[] = {
  B10000000,
  B01000000,
  B00100000,
  B00010000,
  B00001000,
  B00000100
};

const int LEFT_CAR_BUTTON = 2;
const int RIGHT_CAR_BUTTON = 3;
const int PEDASTRIAN_DEADTIME = 5;
const int LEFT_CAR_DEADTIME = 6;
const int RIGHT_CAR_DEADTIME = 7;

void handleTrafficLights() {
  switch (getTrafficLightValue()) {
    case 1:
      Serial.println("Dutch trafficlight active");
      doDutchTrafficLightTask();
      break;
    case 2:
      Serial.println("German trafficlight active");
      doGermanTrafficLightTask();
      break;
    case 3:
      Serial.println("Austrian trafficlight active");
      doAustrianTrafficLightTask();
      break;
    case 4:
      Serial.println("Warning trafficlight active");
      blinkBothOrangeLights();
      break;
    default:
      doDutchTrafficLightTask();
      break;
  }
}

//=========================================Dutch trafficlight tasks=============================================

void doDutchTrafficLightTask() {
  currentTimeDutch = millis();

  if (getButtonTouchedLeftCarValue() == 1 && !startTimerDutchTrafficLights) {
    startTimeDutch = currentTimeDutch;
    turnOnLeftTrafficLights('G');
    startTimerDutchTrafficLights = true;
  } else if (getButtonTouchedRightCarValue() == 1 && !startTimerDutchTrafficLights) {
    startTimeDutch = currentTimeDutch;
    turnOnRightTrafficLights('G');
    startTimerDutchTrafficLights = true;
  }

  //Zet oranje licht aan bij linker of rechter stoplicht
  if (currentTimeDutch - startTimeDutch >= TRAFFICLIGHTDURATIONS[0] && startTimerDutchTrafficLights)
  {
    if (getButtonTouchedLeftCarValue() == 1) {
      turnOnLeftTrafficLights('O');
    } else if (getButtonTouchedRightCarValue() == 1) {
      turnOnRightTrafficLights('O');
    }
  }

  //Reset de button touched waarde op 0, en omdat de waarde 0 is wordt het rode licht geactiveerd.
  //Ook wordt de startTimerTrafficLights gereset zodat je na het het huidige stoplicht ook het andere stoplicht kan activeren
  if (currentTimeDutch - startTimeDutch >= (TRAFFICLIGHTDURATIONS[0] + TRAFFICLIGHTDURATIONS[1]) && startTimerDutchTrafficLights)
  {
    trafficlightDoneTasks();
    startTimerDutchTrafficLights = false; //Reset de timer
  }

  //Zet rode licht aan bij beide stoplichten
  checkIfTurningOnBothRedLights();
}

//=========================================German trafficlight tasks=============================================

void doGermanTrafficLightTask() {
  currentTimeGerman = millis();

  if (getButtonTouchedLeftCarValue() == 1 && !startTimerGermanTrafficLights)
  {
    startTimeGerman = currentTimeGerman;
    turnOnLeftTrafficLights('R');
    startTimerGermanTrafficLights = true;
  }
  else if (getButtonTouchedRightCarValue() == 1 && !startTimerGermanTrafficLights)
  {
    startTimeGerman = currentTimeGerman;
    turnOnRightTrafficLights('R');
    startTimerGermanTrafficLights = true;
  }

  //Is de tijd van oranje + rode licht verstreken? Zet groen licht aan
  if (currentTimeGerman - startTimeGerman >= TRAFFICLIGHTDURATIONS[2] && startTimerGermanTrafficLights)
  {
    if (getButtonTouchedLeftCarValue() == 1)
    {
      turnOnLeftTrafficLights('G');
    }
    else if (getButtonTouchedRightCarValue() == 1)
    {
      turnOnRightTrafficLights('G');
    }
  }

  //Is de tijd van oranje + rode en groen licht verstreken? Zet oranje licht aan
  if (currentTimeGerman - startTimeGerman >= (TRAFFICLIGHTDURATIONS[2] + TRAFFICLIGHTDURATIONS[0]) && startTimerGermanTrafficLights)
  {
    if (getButtonTouchedLeftCarValue() == 1)
    {
      turnOnLeftTrafficLights('O');
    }
    else if (getButtonTouchedRightCarValue() == 1)
    {
      turnOnRightTrafficLights('O');
    }
  }

  //Reset de button touched waarde op 0, en omdat de waarde 0 is wordt het rode licht geactiveerd.
  //Ook wordt de startTimerTrafficLights gereset zodat je na het het huidige stoplicht ook het andere stoplicht kan activeren
  if (currentTimeGerman - startTimeGerman >= (TRAFFICLIGHTDURATIONS[0] + TRAFFICLIGHTDURATIONS[1] + TRAFFICLIGHTDURATIONS[2]) && startTimerGermanTrafficLights)
  {
    trafficlightDoneTasks();
    startTimerGermanTrafficLights = false; //Reset de timer
  }

  //Zet rode licht aan bij beide stoplichten
  checkIfTurningOnBothRedLights();
}


//=========================================Austrian trafficlight tasks=============================================

void doAustrianTrafficLightTask() {
  currentTimeAustrian = millis();

  if (getButtonTouchedLeftCarValue() == 1 && !startTimerAustrianTrafficLights)
  {
    startTimeAustrian = currentTimeAustrian;
    turnOnLeftTrafficLights('R');
    startTimerAustrianTrafficLights = true;
  }
  else if (getButtonTouchedRightCarValue() == 1 && !startTimerAustrianTrafficLights)
  {
    startTimeAustrian = currentTimeAustrian;
    turnOnRightTrafficLights('R');
    startTimerAustrianTrafficLights = true;
  }

  //Is de tijd van oranje + rode licht verstreken? Zet groen licht aan
  if (currentTimeAustrian - startTimeAustrian >= TRAFFICLIGHTDURATIONS[2] && startTimerAustrianTrafficLights)
  {
    if (getButtonTouchedLeftCarValue() == 1)
    {
      turnOnLeftTrafficLights('G');
    }
    else if (getButtonTouchedRightCarValue() == 1)
    {
      turnOnRightTrafficLights('G');
    }
  }

  //Laat groene licht knipperen
  if (currentTimeAustrian - startTimeAustrian >= (TRAFFICLIGHTDURATIONS[2] + TRAFFICLIGHTDURATIONS[0]) && startTimerAustrianTrafficLights)
  {
    if (getButtonTouchedLeftCarValue() == 1)
    {
      blinkLeftGreenLight();
    }
    else if (getButtonTouchedRightCarValue() == 1)
    {
      blinkRightGreenLight();
    }
  }

  //
  if (currentTimeAustrian - startTimeAustrian >= (TRAFFICLIGHTDURATIONS[2] + TRAFFICLIGHTDURATIONS[0] + TRAFFICLIGHTDURATIONS[3]) && startTimerAustrianTrafficLights)
  {
    if (getButtonTouchedLeftCarValue() == 1)
    {
      turnOnLeftTrafficLights('O');
    }
    else if (getButtonTouchedRightCarValue() == 1)
    {
      turnOnRightTrafficLights('O');
    }
  }

  //Reset de button touched waarde op 0, en omdat de waarde 0 is wordt het rode licht geactiveerd.
  //Ook wordt de startTimerTrafficLights gereset zodat je na het het huidige stoplicht ook het andere stoplicht kan activeren
  if (currentTimeAustrian - startTimeAustrian >= (TRAFFICLIGHTDURATIONS[0] + TRAFFICLIGHTDURATIONS[1] + TRAFFICLIGHTDURATIONS[2] + TRAFFICLIGHTDURATIONS[3]) && startTimerAustrianTrafficLights)
  {
    trafficlightDoneTasks();
    startTimerAustrianTrafficLights = false; //Reset de timer
  }

  //Zet rode licht aan bij beide stoplichten
  checkIfTurningOnBothRedLights();
}

//==============================================================================

void trafficlightDoneTasks() {
  resetButtonOrDeadTime(LEFT_CAR_BUTTON);
  resetButtonOrDeadTime(RIGHT_CAR_BUTTON);
  resetButtonOrDeadTime(PEDASTRIAN_DEADTIME);
  resetButtonOrDeadTime(LEFT_CAR_DEADTIME);
  resetButtonOrDeadTime(RIGHT_CAR_DEADTIME);
}

void checkIfTurningOnBothRedLights() {
  if (getButtonTouchedRightCarValue() == 0 && getButtonTouchedLeftCarValue() == 0 && getButtonTouchedTestButtonValue() == 0)
  {
    turnOnOrOffMultipleLights('R');
  }
}

//=================================================================================

void turnOnLeftTrafficLights(char trafficLight) {
  switch (trafficLight) {
    //Groen licht
    case 'G':
      ledPattern = B10000100;
      break;
    //Oranje licht
    case 'O':
      ledPattern = B01000100;
      break;
    //Rood EN oranje licht
    case 'R':
      ledPattern = B01100100;
      break;
    default:
      //nothing
      break;
  }
}

void turnOnRightTrafficLights(char trafficLight) {
  switch (trafficLight) {
    //Groen licht
    case 'G':
      ledPattern = B00110000;
      break;
    //Oranje licht
    case 'O':
      ledPattern = B00101000;
      break;
    //Rood EN oranje licht
    case 'R':
      ledPattern = B00101100;
      break;
    default:
      //nothing
      break;
  }
}

//========================================================================

byte turnOnOrOffMultipleLights(char lights) {
  switch (lights) {
    //R for Red
    case 'R':
      ledPattern = BOTH_TRAFFICLIGHTS_RED;
      break;
    //O for Orange
    case 'O':
      ledPattern = BOTH_TRAFFICLIGHTS_ORANGE;
      break;
    case 1:
      ledPattern = ALL_LEFT_TRAFFICLIGHTS_OFF;
      break;
    case 2:
      ledPattern = ALL_RIGHT_TRAFFICLIGHTS_OFF;
      break;
    case 3:
      ledPattern = ALL_TRAFFICLIGHTS_OFF;
      break;
  }
}

//========================================================================

void blinkLeftGreenLight() {
  unsigned long currentMillisLeftBlinkingGreen = millis();
  int leftLights = 1;

  turnOnOrOffMultipleLights(leftLights);

  if (currentMillisLeftBlinkingGreen - previousMillisLeftBlinkingGreen >= TRAFFICLIGHTDURATIONS[4]) {
    previousMillisLeftBlinkingGreen = currentMillisLeftBlinkingGreen;
    turnOnLeftTrafficLights('G');
  }
}

void blinkRightGreenLight() {
  unsigned long currentMillisRightBlinkingGreen = millis();
  int rightLights = 2;

  //While not in the if loop turn off all right lights
  turnOnOrOffMultipleLights(rightLights);

  //After 0.5 seconds turn green light on
  if (currentMillisRightBlinkingGreen - previousMillisRightBlinkingGreen >= TRAFFICLIGHTDURATIONS[4]) {
    previousMillisRightBlinkingGreen = currentMillisRightBlinkingGreen;
    turnOnRightTrafficLights('G');
  }
}

void blinkBothOrangeLights() {
  currentTimeOrangeBlinking = millis();

  //For 0.5 seconds turn on all orange lights
  if (!startTimerBlinkingOrange) {
    startTimeOrangeBlink = currentTimeOrangeBlinking;
    turnOnOrOffMultipleLights('O');
    startTimerBlinkingOrange = true;
  }

  //After 0.5 seconds turn off all lights
  if (currentTimeOrangeBlinking - startTimeOrangeBlink >= TRAFFICLIGHTDURATIONS[4] && startTimerBlinkingOrange) {
    turnOnOrOffMultipleLights(3);
  }

  //After a period is done reset the timer so it can start over again
  if (currentTimeOrangeBlinking - startTimeOrangeBlink >= TRAFFICLIGHTDURATIONS[5] && startTimerBlinkingOrange) {
    startTimerBlinkingOrange = false;
  }
}

void turnOnAllLightsConsecutively() {
  unsigned long currentMillisTestingLights = millis();
  static int led = 0;

  if (currentMillisTestingLights - previousMillisTestingLights >= TRAFFICLIGHTDURATIONS[6]) {
    previousMillisTestingLights = currentMillisTestingLights;

    turnOnLightForTest(TEST_ALL_LIGHTS[led]);
    led++;

    if (led >= 6) {
      led = 0;
    }
  }
}

//===============================================================================

byte getLedPattern() {
  return ledPattern;
}

byte turnOnLightForTest(byte pattern) {
  ledPattern = pattern;
}
