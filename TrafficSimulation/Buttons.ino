/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

const int BUTTONPIN_ARRAY[] = {
  6, //Left car button pin
  7, //Pedastrian button pin
  8, //Right car button pin
  10
};

unsigned long startDeadTimeLeftCar, startDeadTimeRightCar, startDeadTimePedastrian;
unsigned long deadTimeDuration = 4000;

boolean startTimerDeadTimeLeftCar, startTimerDeadTimeRightCar, startTimerDeadTimePedastrian;

static int buttonStatePedastrian, buttonStateLeftCar, buttonStateRightCar, buttonStateTestButton;
static int buttonTouchedPedastrian, buttonTouchedLeftCar, buttonTouchedRightCar, buttonTouchedTestButton = 0;

byte buttonIsPressed = 1;
byte leftCarButton = 0;
byte pedastrianButton = 1;
byte rightCarButton = 2;
byte testButton = 3;

void buttonSetup() {
  pinMode(BUTTONPIN_ARRAY[leftCarButton], INPUT);
  pinMode(BUTTONPIN_ARRAY[pedastrianButton], INPUT);
  pinMode(BUTTONPIN_ARRAY[rightCarButton], INPUT);
  pinMode(BUTTONPIN_ARRAY[testButton], INPUT);
}

void handleTrafficButtons() {
  //Checkt constant of er 1 van de 3 knoppen word ingedrukt
  pedastrianButtonIsTouched();
  leftCarButtonIsTouched();
  rightCarButtonIsTouched();
  testButtonIsTouched();
}


//===========================================BUTTON TOUCHED METHODS===================================================================================

void pedastrianButtonIsTouched() {
  int buttonStatePedastrian = digitalRead(BUTTONPIN_ARRAY[1]); //read the state of the pushbutton value
  unsigned long currentMillisDeadTimePedastrian = millis();
  int pedastrianButton = 1;

  //Checks if trafficLightIsNotActive, if so, checks whether startTimerDeadTimePedastrian is false, if checks after deadTimeDuration if button is pressed and if so: setPedastrianButtonValueToOne
  if (trafficLightsNotActive()) {
    if (!startTimerDeadTimePedastrian) {
      startDeadTimePedastrian = currentMillisDeadTimePedastrian;
      startTimerDeadTimePedastrian = true;
    }

    if (currentMillisDeadTimePedastrian - startDeadTimePedastrian >= deadTimeDuration && startTimerDeadTimePedastrian) {
      if (buttonStatePedastrian == buttonIsPressed) {
        setButtonValueToOne(pedastrianButton);
      }
    }
  }
}

void leftCarButtonIsTouched() {
  int buttonStateLeftCar = digitalRead(BUTTONPIN_ARRAY[0]); //read the state of the pushbutton value
  unsigned long currentMillisDeadTimeLeftCar = millis();
  int leftCarButton = 2;

  //Zet de waarde omhoog zodra er gedrukt is
  if (pedastrianCrossingNotActive()) {
    if (!startTimerDeadTimeLeftCar) {
      startDeadTimeLeftCar = currentMillisDeadTimeLeftCar;
      startTimerDeadTimeLeftCar = true;
    }

    if (currentMillisDeadTimeLeftCar - startDeadTimeLeftCar >= deadTimeDuration && startTimerDeadTimeLeftCar) {
      if (buttonStateLeftCar == buttonIsPressed) {
        setButtonValueToOne(leftCarButton);
      }
    }
  }
}

void rightCarButtonIsTouched() {
  int buttonStateRightCar = digitalRead(BUTTONPIN_ARRAY[2]); //read the state of the pushbutton value
  unsigned long currentMillisDeadTimeRightCar = millis();
  int rightCarButton = 3;

  //Zet de waarde omhoog zodra er gedrukt is
  if (pedastrianCrossingNotActive()) {
    if (!startTimerDeadTimeRightCar) {
      startDeadTimeRightCar = currentMillisDeadTimeRightCar;
      startTimerDeadTimeRightCar = true;
    }

    if (currentMillisDeadTimeRightCar - startDeadTimeRightCar >= deadTimeDuration && startTimerDeadTimeRightCar) {
      if (buttonStateRightCar == buttonIsPressed) {
        setButtonValueToOne(rightCarButton);
      }
    }
  }
}

void testButtonIsTouched() {
  int buttonStateTestButton = digitalRead(BUTTONPIN_ARRAY[3]); //read the state of the pushbutton value
  int testButton = 4;

  //Zet de waarde omhoog zodra er gedrukt is
  if (buttonStateTestButton == buttonIsPressed) {
    setButtonValueToOne(testButton);
  }
}

//=======================================================SET BUTTONTOUCHED VALUE======================================================

byte setButtonValueToOne(int button) {
  switch (button) {
    case 1:
      buttonTouchedPedastrian = 1;
      break;
    case 2:
      buttonTouchedLeftCar = 1;
      break;
    case 3:
      buttonTouchedRightCar = 1;
      break;
    case 4:
      buttonTouchedTestButton = 1;
      break;
  }
}

//========================================================GET BUTTONTOUCHED VALUE======================================================

byte getButtonTouchedPedastrianValue() {
  return buttonTouchedPedastrian;
}

byte getButtonTouchedLeftCarValue() {
  return buttonTouchedLeftCar;
}

byte getButtonTouchedRightCarValue() {
  return buttonTouchedRightCar;
}

byte getButtonTouchedTestButtonValue() {
  return buttonTouchedTestButton;
}

//========================================================RESET METHODS======================================================

byte resetButtonOrDeadTime(int key) {
  switch (key) {
    case 1:
      buttonTouchedPedastrian = 0;
      break;
    case 2:
      buttonTouchedLeftCar = 0;
      break;
    case 3:
      buttonTouchedRightCar = 0;
      break;
    case 4:
      buttonTouchedTestButton = 0;
      break;
    case 5:
      startTimerDeadTimePedastrian = false;
      break;
    case 6:
      startTimerDeadTimeLeftCar = false;
      break;
    case 7:
      startTimerDeadTimeRightCar = false;
      break;
  }
}

//========================================================CHECK IF CROSSINGS ARE ACTIVE OR NOT======================================================

boolean trafficLightsNotActive() {
  boolean trafficLightsAreNotActive;

  if (getButtonTouchedLeftCarValue() == 0 && getButtonTouchedRightCarValue() == 0) {
    trafficLightsAreNotActive = true;
    //    Serial.println((String) " Traffic lights are not active!");
  } else {
    trafficLightsAreNotActive = false;
  }
  return trafficLightsAreNotActive;
}

boolean pedastrianCrossingNotActive() {
  boolean PedastrianCrossingNotActive;

  if (getButtonTouchedPedastrianValue() == 0) {
    PedastrianCrossingNotActive = true;
    //    Serial.println((String) " Pedastrian crossing not active!");
  } else {
    PedastrianCrossingNotActive = false;
  }
  return PedastrianCrossingNotActive;
}
