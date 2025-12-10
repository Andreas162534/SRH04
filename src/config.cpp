#include "config.h"

// geometry
const float D = 30.0;
const float h = 50.0;

// pins
const int trigA = 10;
const int echoA = 9;
const int trigB = 12;
const int echoB = 11;

const int trigTX = 4;   // or whatever you use

// global parameters
int avgN = 3;
const float c_mm_per_us = 0.343;  // adjust if needed