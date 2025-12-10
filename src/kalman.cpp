#include <Arduino.h>
#include "kalman.h"

float xKF = 0, yKF = 0;
float vxKF = 0, vyKF = 0;

bool useKalman = true;

float R = 4.0;
float Q = 0.1;

void kalman2D(float &x, float &y){
    float K = Q / (Q + R);

    xKF += vxKF;
    yKF += vyKF;

    xKF += K * (x - xKF);
    yKF += K * (y - yKF);

    x = xKF;
    y = yKF;
}
