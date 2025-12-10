#pragma once

extern float xKF, yKF, vxKF, vyKF;
extern bool useKalman;

void kalman2D(float &x, float &y);