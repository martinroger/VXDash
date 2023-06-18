/*
Potentiometers (1K or more) connected to A0 A1 A2 qnd A3
Outputs are on D2 D3 and D13
Mapping as follows:
D2 -> Speed 
D3 -> RPM
D13 -> Water temp PWM
A0 duty cycle for D2 and D3
A1 Speed freq
A2 RPM freq
A3 Duty cycle Water T
*/
#include <Arduino_Helpers.h>
#include <AH/Timing/MillisMicrosTimer.hpp>

Timer<millis> potUpdateTimer = 100;
Timer<micros> speedTimerOn = 10000;
Timer<micros> speedTimerOff = 5000;
Timer<micros> rpmTimerOn = 10000;
Timer<micros> rpmTimerOff = 5000;
Timer<micros> waterTimerOn = 10000;
Timer<micros> waterTimerOff = 1000;

int speedFreq = 1;
unsigned long speedInterval = 1000000;
int rpmFreq = 1;
unsigned long rpmInterval = 1000000;
int waterT_DC = 10;

bool debug=false;

int rawA0 = 0;
int rawA1 = 0;
int rawA2 = 0;
int rawA3 = 0;


void refreshPots() {
  rawA0 = analogRead(A0); //generate DC
  if(debug) {Serial.print(rawA0); Serial.print(" ");}
  rawA1 = analogRead(A1); //Speed
  if(debug) {Serial.print(rawA1); Serial.print(" ");}
  rawA2 = analogRead(A2); //RPM
  if(debug) {Serial.print(rawA2); Serial.print(" ");}
  rawA3 = analogRead(A3); //Water
  if(debug) Serial.println(rawA3);
  
  speedFreq = map(rawA1,0,1023,1,987);
  if(debug) {Serial.print(speedFreq); Serial.print(" ");}
  speedInterval = 1000000/speedFreq;
  if(speedTimerOn.getInterval()!=speedInterval) {
    speedTimerOn.setInterval(speedInterval);
    speedTimerOff.setInterval(speedInterval*20/100);
  }
  
  rpmFreq   = map(rawA2,0,1023,1,14000/60);
  if(debug) {Serial.print(rpmFreq); Serial.print(" ");}
  rpmInterval =1000000/rpmFreq;
  if(rpmTimerOn.getInterval()!=rpmInterval) {
    rpmTimerOn.setInterval(rpmInterval);
    rpmTimerOff.setInterval(rpmInterval*20/100);
  }
  
  waterT_DC = map(rawA3,0,1023,10,95);
  if(debug) {Serial.println(waterT_DC);}
  if(waterTimerOff.getInterval()!=(waterT_DC*10000/100)) {
    waterTimerOff.setInterval(waterT_DC*10000/100);
  }

}



void setup() {
  if(debug) Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);
}

void loop() {
  if(potUpdateTimer) refreshPots();
  if(speedTimerOn) {
    digitalWrite(2,HIGH);
    speedTimerOff.beginNextPeriod();
  }
  if(speedTimerOff) digitalWrite(2,LOW);
  if(rpmTimerOn) {
    digitalWrite(3,HIGH);
    rpmTimerOff.beginNextPeriod();
  }
  if(rpmTimerOff) digitalWrite(3,LOW);
  if(waterTimerOn) {
    digitalWrite(13,HIGH);
    waterTimerOff.beginNextPeriod();
  }
  if(waterTimerOff) digitalWrite(13,LOW);
}


