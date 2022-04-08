/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

unsigned long startTimeTesting, currentTimeTesting = 0;
boolean startTimerTesting = false;

const int TEST_COMPONENTS_DURATIONS[] = {
  6000,
  3000,
  3000,
};

const int LED_TESTING = 0;
const int DISPLAY_TESTING = 1;
const int BUZZER_TESTING = 2;

void handleTrafficTasks() {
  handleTrafficButtons();
  handlePedastrianTasks();
  sendToShiftRegisters();
  handleTrafficLights();
  readSerial();
  switchTraffcLightValue();
}

void testAllComponents() {
  currentTimeTesting = millis();
  int testButton = 4;

  if (!startTimerTesting) {
    startTimeTesting = currentTimeTesting;
    startTimerTesting = true;
  }

  if (currentTimeTesting - startTimeTesting >= 0 && currentTimeTesting - startTimeTesting <= TEST_COMPONENTS_DURATIONS[0] && startTimerTesting) {
    turnOnAllLightsConsecutively();
  }

  //If light testing done, test display and turn off lights
  if (currentTimeTesting - startTimeTesting >= TEST_COMPONENTS_DURATIONS[0] && startTimerTesting) {
    displaySigns('T');
    turnOnOrOffMultipleLights(3);
  }

  //If display testing done, test buzzer and turn off display
  if (currentTimeTesting - startTimeTesting >= (TEST_COMPONENTS_DURATIONS[0] + TEST_COMPONENTS_DURATIONS[1]) && startTimerTesting) {
    doBuzzerTaskWalking();
    displaySigns('N');
  }

  if (currentTimeTesting - startTimeTesting >= (TEST_COMPONENTS_DURATIONS[0] + TEST_COMPONENTS_DURATIONS[1] + TEST_COMPONENTS_DURATIONS[2]) && startTimerTesting) {
    if (isBarrierOpen()) {
      closeBarrier();
    } else {
      openBarrier();
    }
  }

  if (currentTimeTesting - startTimeTesting >= (TEST_COMPONENTS_DURATIONS[0] + TEST_COMPONENTS_DURATIONS[1] + TEST_COMPONENTS_DURATIONS[2] + TEST_COMPONENTS_DURATIONS[0]) && startTimerTesting) {
    resetButtonOrDeadTime(testButton);
    startTimerTesting = false;
  }
}
