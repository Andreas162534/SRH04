#pragma once
#include <Arduino.h>

// geometry (cm)
extern const float D;            // sensor spacing
extern const float h;            // sensor height

// pins
extern const int trigA, echoA;
extern const int trigB, echoB;
extern const int trigTX;         // if you use the bistatic mode

// measurement
extern int   avgN;
extern const float c_mm_per_us;  // for bistatic TOF

// options
extern bool useKalman;