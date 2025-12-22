//1TX, in object plane, not usable!

#include <Arduino.h>
#include "config.h"
#include "kalman.h"

// measure total TOF for (TX → object → echo)
float measureAvgTOF(int trig, int echo, int N) {
    float s = 0;
    for (int i = 0; i < N; i++) {
        digitalWrite(trig, LOW); delayMicroseconds(2);
        digitalWrite(trig, HIGH); delayMicroseconds(10);
        digitalWrite(trig, LOW);

        long dur = pulseIn(echo, HIGH);
        s += (float)dur;
        delay(10);
    }
    return s / N;
}

void bistaticSetup() {
    pinMode(trigTX, OUTPUT);
    pinMode(echoA, INPUT);
    pinMode(echoB, INPUT);

    Serial.begin(9600);
}

void bistaticLoop() {

    float tofA = measureAvgTOF(trigTX, echoA, 3);
    float tofB = measureAvgTOF(trigTX, echoB, 3);

    float LA = v * tofA;   // mm
    float LB = v * tofB;   // mm

    float rA = 0.5f * LA;            // object→A (mm)
    float rB = LB - rA;              // object→B (mm)
    if (rA < 0 || rB < 0) return;

    float x = (rA*rA - rB*rB + D*D) / (2.0f * D);
    float y2 = rA*rA - x*x;
    float y  = (y2 > 0.0f) ? sqrtf(y2) : 0.0f;

    if (useKalman) kalman2D(x, y);

    Serial.print("B-mode  X=");
    Serial.print(x);
    Serial.print("  Y=");
    Serial.println(y);

    delay(30);
}
