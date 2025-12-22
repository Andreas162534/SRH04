#include <Arduino.h>
#include "triangulation.h"
#include "above.h"

void setup() {
    aboveSetup();   // calls the code in above.cpp
}

void loop() {
    aboveLoop();    // runs every cycle
}


//void setup() {
//    triangulationSetup();
//}

//void loop() {
//    triangulationLoop();
//}