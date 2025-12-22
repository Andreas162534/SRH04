#include "config.h"

const float D           = 15.0f;     // 15 cm
const float h           = 55.0f;     // 30 cm
const int   trigA       = 11;     //first sensor sits lift 
const int   echoA       = 12;        
const int   trigB       = 9;     //second sensor sits right
const int   echoB       = 10;


int         avgN        = 3;
const float v           = 0.0343f;    // ~343 m/s = 0.0343 cm/us 

bool        useKalman   = false;