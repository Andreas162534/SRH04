#include <Arduino.h>
//cork, eva foam, carpet!
// =====================
bool useKalman = true;      // turn Kalman filtering on/off
int avgN = 3;               // number of samples to average

// =====================
// GEOMETRY
// =====================
const float D = 30.0;
const float h = 50.0;

// PINS
const int trigA = 10, echoA = 9;
const int trigB = 12, echoB = 11;

// =====================
// Basic distance
// =====================
float measureRaw(int trig, int echo) {
  digitalWrite(trig, LOW); delayMicroseconds(2);
  digitalWrite(trig, HIGH); delayMicroseconds(10);
  digitalWrite(trig, LOW);
  long dur = pulseIn(echo, HIGH);
  return dur * 0.0343 / 2.0;
}

float measureAvg(int trig, int echo, int N){
  float s = 0;
  for(int i=0;i<N;i++){
    s += measureRaw(trig, echo);
    delay(10);
  }
  return s / N;
}

// =====================
// Kalman filter state
// =====================
float xKF=0, yKF=0;
float vxKF=0, vyKF=0;

float R = 4.0;     // measurement noise #the higher the less influece have recent measurements
float Q = 0.1;     // process noise #the higher the more the filter smooths the output
// the higher the gain, the more response to measurments it isQ

void kalman2D(float &x, float &y){
  // Predict
  xKF += vxKF;
  yKF += vyKF;

  // Update (scalar gain)
  float K = Q / (Q + R);

  xKF += K * (x - xKF);
  yKF += K * (y - yKF);

  // Output filtered
  x = xKF;
  y = yKF;
}

// =====================
// ARDUINO SETUP
// =====================
void setup() {
  Serial.begin(9600);
  pinMode(trigA, OUTPUT); pinMode(echoA, INPUT);
  pinMode(trigB, OUTPUT); pinMode(echoB, INPUT);
}

// =====================
// MAIN LOOP
// =====================
void loop() {

  float dA = measureAvg(trigA, echoA, avgN);
  delay(40);
  float dB = measureAvg(trigB, echoB, avgN);

  // Trilateration
  float x = (dA*dA - dB*dB + D*D) / (2.0 * D);

  float y2 = dA*dA - h*h - x*x;
  float y  = (y2 > 0) ? sqrt(y2) : 0;

  if(useKalman){
    kalman2D(x, y);
  }

  Serial.print("X=");
  Serial.print(x);
  Serial.print("  Y=");
  Serial.println(y);

  delay(20);
}
