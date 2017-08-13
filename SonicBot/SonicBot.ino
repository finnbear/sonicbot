int leftMotorDirectionPin = 8;
int leftMotorSpeedPin = 9;
int rightMotorDirectionPin = 2;
int rightMotorSpeedPin = 3;

int sonicServoPin = 5;
int sonicTriggerPin = 4;
int sonicEchoPin = 7;

void setup() {
  pinMode(leftMotorDirectionPin, OUTPUT);
  pinMode(leftMotorSpeedPin, OUTPUT);
  pinMode(rightMotorDirectionPin, OUTPUT);
  pinMode(rightMotorSpeedPin, OUTPUT);

  pinMode(sonicServoPin, OUTPUT);
  pinMode(sonicTriggerPin, OUTPUT);
  pinMode(sonicEchoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:

}
