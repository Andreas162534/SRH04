#include "config.h"

const float D           = 200.0f;     // 20 cm
const float h           = 300.0f;     // 30 cm
const int   trigA       = 2;
const int   echoA       = 3;
const int   trigB       = 4;
const int   echoB       = 5;
const int   trigTX      = 6;         // if used

int         avgN        = 3;
const float c_mm_per_us = 0.343f;    // ~343 m/s

bool        useKalman   = false;