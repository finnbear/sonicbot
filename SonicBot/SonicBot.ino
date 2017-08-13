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
int sonicServoMin = 0;
int sonicServoMax = 130;
int sonicSteps;

void setup() {
  pinMode(leftMotorDirectionPin, OUTPUT);
  pinMode(leftMotorSpeedPin, OUTPUT);
  pinMode(rightMotorDirectionPin, OUTPUT);
  pinMode(rightMotorSpeedPin, OUTPUT);

  pinMode(sonicServoPin, OUTPUT);
  pinMode(sonicTriggerPin, OUTPUT);
  pinMode(sonicEchoPin, INPUT);

  sonicServo.attach(sonicServoPin);
  sonicServo.write(90);

  sonicSteps = (sonicServoMax - sonicServoMin) / sonicServoIncrement;

  Serial.begin(9600);
  while (!Serial) {
    
  }
}

int ping(int angle) {
  sonicServo.write(angle);
  delay(100);
  
  digitalWrite(sonicTriggerPin, LOW);
  delayMicroseconds(2);
  digitalWrite(sonicTriggerPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(sonicTriggerPin, LOW);

  return pulseIn(sonicEchoPin, HIGH) / 50 / 2;
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
  long testMin = 2147483647L;
  long testMax = 0;

  for (int i = 0; i < sonicSteps; i++) {
    if (testAveraged[i] < testMin) {
      testMin = testAveraged[i];
    }

    if (testAveraged[i] > testMax) {
      testMax = testAveraged[i];
    }
  }

  Serial.print("Min: ");
  Serial.println(testMin);

  Serial.print("Max: ");
  Serial.println(testMax);

  for (int i = 0; i < sonicSteps; i++) {
    testNormalized[i] = (float)(testAveraged[i] - testMin) / (testMax - testMin);
  }
}

void loop() {
  long testAveraged[sonicSteps];

  scan(testAveraged);

  Serial.print("Averages: ");
  for (int i = 0; i < sonicSteps; i++) {
    Serial.print(testAveraged[i]);
    Serial.print(", ");
  }

  Serial.println("");
  
  float testNormalized[sonicSteps];

  normalize(testAveraged, testNormalized);

  Serial.print("Normals: ");
  for (int i = 0; i < sonicSteps; i++) {
    Serial.print(testNormalized[i]);
    Serial.print(", ");
  }

  Serial.println("");

  delay(5000);
}
