/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

unsigned long startTimePedastrian;
unsigned long currentTimePedastrian;
boolean startTimerPedastrian = false;

const int DISPLAY_DURATION[] = {
  5000, //Walking duration
  6200  //Countdown duration
};

void handlePedastrianTasks() {
  doPedastrianTrafficTask();
}

void doPedastrianTrafficTask() {
  if (getButtonTouchedPedastrianValue() == 1 && getServoReadValue() < 180) {
    doBarrierTask('O');
  }

  //Defineer pas de currentTimePedastrian na de bovenste statement, anders gaat hij tijdens het open van de slagboom al tellen
  currentTimePedastrian = millis();

  //Start de timer en start het tijd deel wanneer je kan lopen
  if (getButtonTouchedPedastrianValue() == 1 && isBarrierOpen() && !startTimerPedastrian) {
    startTimePedastrian = currentTimePedastrian;
    startTimerPedastrian = true;
    displaySigns('L');
  }

  //Checkt of de tijd kleiner is dan 5000ms en voert zodra TRUE het buzzer geluid af bij het lopen
  if (currentTimePedastrian - startTimePedastrian <= DISPLAY_DURATION[0] && startTimerPedastrian) {
    doBuzzerTaskWalking();
  }

  //Telt van 6 naar 0 met een passend buzzer geluid
  if (currentTimePedastrian - startTimePedastrian >= DISPLAY_DURATION[0] && startTimerPedastrian) {
    setDisplayPatternCountdown();
    doBuzzerTaskCountdown();
  }

  //Zodra de verstreken tijd groter is dan de bij opgetelde durations, reset de button value en reset de timer
  if (currentTimePedastrian - startTimePedastrian >= (DISPLAY_DURATION[0] + DISPLAY_DURATION[1]) && startTimerPedastrian) {
    closingBarrierStateTasks();
    startTimerPedastrian = false;
  }

  //Zodra de button value 0 is laat het stopteken zien en speel om de seconde een tik af
  if (getButtonTouchedPedastrianValue() == 0 && getButtonTouchedTestButtonValue() == 0) {
    doNormalStateTasks();
  }
}

void doNormalStateTasks() {
  displaySigns('S');
  doBuzzerNormalState();
}

void closingBarrierStateTasks() {
  int pedastrianButton = 1;
  int pedastrianDeadTime = 5;

  doBarrierTask('C');
  resetButtonOrDeadTime(pedastrianDeadTime);
  resetButtonOrDeadTime(pedastrianButton);
}
