#include <Servo.h>

int leftMotorDirectionPin = 8;
int leftMotorSpeedPin = 9;
int rightMotorDirectionPin = 2;
int rightMotorSpeedPin = 3;

int sonicServoPin = 5;
int sonicTriggerPin = 4;
int sonicEchoPin = 7;
Servo sonicServo;

int sonicServoIncrement = 5;
int sonicServoMin = 10;
int sonicServoMax = 170;
int sonicSteps;

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    
  }
  
  pinMode(leftMotorDirectionPin, OUTPUT);
  pinMode(leftMotorSpeedPin, OUTPUT);
  pinMode(rightMotorDirectionPin, OUTPUT);
  pinMode(rightMotorSpeedPin, OUTPUT);

  pinMode(sonicServoPin, OUTPUT);
  pinMode(sonicTriggerPin, OUTPUT);
  pinMode(sonicEchoPin, INPUT);

  sonicServo.attach(sonicServoPin);

  sonicSteps = (sonicServoMax - sonicServoMin) / sonicServoIncrement;
}

int ping(int angle) {
  sonicServo.write(angle);
  delay(100);
  
  digitalWrite(sonicTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonicTriggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonicTriggerPin, LOW);

  return pulseIn(sonicEchoPin, HIGH);
}

void scan(long *testAveraged) {
  long test1[sonicSteps];

  int pos = 0;
  for (int i = sonicServoMin; i <= sonicServoMax; i++) {
    
    test1[pos++] = ping(i);
  }

  pos = 0;
  for (int i = sonicServoMax; i >= sonicServoMin; i--) {
    testAveraged[pos] = (ping(i) + test1[pos++]) / 2;
  }
}

void normalize(long *testAveraged, float *testNormalized) {
  long testMin = 1000l * 1000l;
  long testMax = 0;

  for (int i = 0; i < sonicSteps; i++) {
    if (testAveraged[i] < testMin) {
      testMin = testAveraged[i];
    }

    if (testAveraged[i] > testMax) {
      testMax = testAveraged[i];
    }
  }

  for (int i = 0; i < sonicSteps; i++) {
    testNormalized[i] = map(testAveraged[i], testMin, testMax, 0, 1000) / (float)1000;
  }
}

void loop() {
  long testAveraged[sonicSteps];

  scan(testAveraged);
  
  float testNormalized[sonicSteps];

  normalize(testAveraged, testNormalized);

  for (int i = 0; i < sonicSteps; i++) {
    Serial.print(testNormalized[i]);
    Serial.print(", ");
  }

  Serial.println("");

  delay(5000);
}
