/*
 *SKETCH Trafficsimulation 
 *AUTEUR Mick Waanders
 *DATE: 16-12-2021
*/

int baudRate = 9600;

void setup() {
  Serial.begin(baudRate);
  buzzerSetup(); //Setup voor de buzzer
  servoSetup(); //Setup voor de Servo
  buttonSetup(); //Setup voor de button
  displaySetup(); //Setup voor het display
};

void loop() {
  handleTrafficTasks();

  if (getButtonTouchedTestButtonValue() == 1) {
    testAllComponents();    
  }
};
