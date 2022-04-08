/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

const int BUZZER_PIN = 5;
const int BUZZER_INTERVALS[] = {
  100, //Countdown interval
  350, //Walking display interval
  1000 //Normal interval
};

unsigned long int previousMillisCountdown;
unsigned long int previousMillisWalking;
unsigned long int previousMillisNormalState;

void buzzerSetup() {
  pinMode(BUZZER_PIN, OUTPUT);
}

void doBuzzerTaskCountdown() {
  unsigned long currentMillisCountdown = millis();
  static int countdownInterval = 200;
  static int nrTimesLooped;

  if (currentMillisCountdown - previousMillisCountdown >= countdownInterval) {
    previousMillisCountdown = currentMillisCountdown;

    //Checkt of de tijd onder de 12 seconden blijft en voert de functies in de if uit, anders niet
    nrTimesLooped++;
    countdownInterval = 200;
    playBuzzerTone(2);

    //Zodra het aantal keren afgespeeld groter of gelijk is aan 3, wordt het aantal keren gereset en word de interval voor 1 keer 750 miliseconden
    if (nrTimesLooped >= 3) {
      nrTimesLooped = 0;
      countdownInterval = 700;
    }
  }
}

void doBuzzerTaskWalking() {
  unsigned long currentMillisWalking = millis();

  if (currentMillisWalking - previousMillisWalking >= BUZZER_INTERVALS[1]) {
    previousMillisWalking = currentMillisWalking;
    playBuzzerTone(2);
  }
}

void doBuzzerNormalState() {
  unsigned long currentMillisNormalState = millis();

  if (currentMillisNormalState - previousMillisNormalState >= BUZZER_INTERVALS[2]) {
    previousMillisNormalState = currentMillisNormalState;
    playBuzzerTone(2);
  }
}

void playBuzzerTone(int duration) {
  tone(BUZZER_PIN, 2000, duration);
}
