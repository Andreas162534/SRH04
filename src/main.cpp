#include <Arduino.h>
//assume positive y put sensors at 0,0 and D,0!!! on x axis straigt facing down, adjsut h, D and sensor pins!
// Abstand zwischen den Sensoren in cm
const float D = 16.0;       // z. B. 20 cm

// Sensor A Pins
const int trigA = 11;
const int echoA = 12;

// Sensor B Pins
const int trigB = 10;
const int echoB = 9;

float measure(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  long duration = pulseIn(echo, HIGH);
  float distance = duration * 0.0343 / 2.0; // cm
  return distance;
}

void setup() {
  Serial.begin(9600);

  pinMode(trigA, OUTPUT);
  pinMode(echoA, INPUT);

  pinMode(trigB, OUTPUT);
  pinMode(echoB, INPUT);
}

void loop() {
  float dA = measure(trigA, echoA);
  float dB = measure(trigB, echoB);

  // Triangulation
  float x = (dA*dA - dB*dB + D*D) / (2.0*D);
  float y = sqrt(max(0.0f, dA*dA - x*x));

  Serial.print("dA: ");
  Serial.print(dA);
  Serial.print("  dB: ");
  Serial.print(dB);
  Serial.print("  -> X: ");
  Serial.print(x);
  Serial.print(" cm, Y: ");
  Serial.print(y);
  Serial.println(" cm");

  delay(100);
}
