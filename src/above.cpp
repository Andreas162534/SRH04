#include <Arduino.h>
#include "config.h"
#include "kalman.h"

// raw ultrasonic distance (cm)
float measureRaw(int trig, int echo) {
    digitalWrite(trig, LOW); delayMicroseconds(2);
    digitalWrite(trig, HIGH); delayMicroseconds(10);
    digitalWrite(trig, LOW);

    long dur = pulseIn(echo, HIGH);
    return dur * 0.0343f / 2.0f;
}

float measureAvg(int trig, int echo, int N) {
    float s = 0;
    for (int i = 0; i < N; i++) {
        s += measureRaw(trig, echo);
        delay(10);
    }
    return s / N;
}

void aboveSetup() {
    pinMode(trigA, OUTPUT);
    pinMode(echoA, INPUT);
    pinMode(trigB, OUTPUT);
    pinMode(echoB, INPUT);

    Serial.begin(9600);
}

void aboveLoop() {

    float dA = measureAvg(trigA, echoA, avgN);
    delay(40);
    float dB = measureAvg(trigB, echoB, avgN);

    float x = (dA*dA - dB*dB + D*D) / (2.0f * D);

    float y2 = dA*dA - h*h - x*x;
    float y  = (y2 > 0.0f) ? sqrtf(y2) : 0.0f;

    if (useKalman) kalman2D(x, y);

    Serial.print("A-mode  X=");
    Serial.print(x);
    Serial.print("  Y=");
    Serial.println(y);

    delay(20);
}