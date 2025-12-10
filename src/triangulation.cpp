#include <Arduino.h>
#include "config.h"
#include "triangulation.h"

// measure distance for one HC-SR04 (cm)
static float measure(int trig, int echo) {
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long duration = pulseIn(echo, HIGH);
    float distance = duration * 0.0343f / 2.0f; // cm
    return distance;
}

// call from main.cpp: setup()
void triangulationSetup() {
    Serial.begin(9600);

    pinMode(trigA, OUTPUT);
    pinMode(echoA, INPUT);

    pinMode(trigB, OUTPUT);
    pinMode(echoB, INPUT);
}

// call from main.cpp: loop()
void triangulationLoop() {
    float dA = measure(trigA, echoA);
    float dB = measure(trigB, echoB);

    // Triangulation (sensors at (0,0) and (D,0))
    float x = (dA*dA - dB*dB + D*D) / (2.0f * D);
    float y = sqrtf(max(0.0f, dA*dA - x*x));

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
