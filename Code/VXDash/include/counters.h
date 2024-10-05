#pragma once
#include <Arduino.h>
#include <Arduino_Helpers.h>
#include <AH/Timing/MillisMicrosTimer.hpp>
#include <AH/STL/cmath>
#include <Filters/SMA.hpp>
#include <pinsDef.h>
#include <stateVars.h>

#define SPEED_MUL 1763/7209
#define PULSES_100M 1485
#define RPM_MUL 30
#define COOL_MUL 71.469
#define COOL_ADD 63.828
#define COOL_TRIGGER_HI 100
#define COOL_TRIGGER_LO 95

//Speed and distance sensing
#pragma region 
volatile uint16_t speedPulseCounter = 0;  //Counter of pulses
volatile uint16_t distPulseCounter = 0;
SMA<10,uint16_t,uint16_t> speedPulseSMA = {0};
void IRAM_ATTR speedPulse() {
  speedPulseCounter++;
  distPulseCounter++;
}
void senseSpeed() {
  //p_speed_raw = speed_raw;
  //p_speed = speed;
  speed_raw = speedPulseSMA(10*speedPulseCounter);
  speedPulseCounter = 0;
  speed = speed_raw * SPEED_MUL;
}
void senseDistance(uint32_t* odoDist, uint16_t* tripDist) {
  if(distPulseCounter >= PULSES_100M) {
    *odoDist = *odoDist + distPulseCounter/PULSES_100M;
    *tripDist = *tripDist + distPulseCounter/PULSES_100M;
    distPulseCounter = distPulseCounter % PULSES_100M;
  }
  if(buttonON) *tripDist = 0;
}
#pragma endregion

//RPM sensing
#pragma region 
volatile uint16_t rpmPulseCounter = 0;
SMA<10,uint16_t,uint16_t> rpmPulseSMA = {0};
void IRAM_ATTR rpmPulse() {
  rpmPulseCounter++;
}
void senseRPM() {
  //p_rpm_raw = rpm_raw;
  //p_rpm = rpm;
  rpm_raw = rpmPulseSMA(10*rpmPulseCounter);
  rpmPulseCounter = 0;
  if (rpm_raw<5) rpm_raw = 0;
  rpm = rpm_raw * RPM_MUL;
}
#pragma endregion

//Coolant sensing
#pragma region 
volatile uint32_t coolant_tmstp = 0;           //Microseconds
volatile uint16_t coolant_deltaTime = 1000;    //Microseconds
SMA<10,uint16_t,uint32_t> coolantDeltaTimeSMA = {1000};
void IRAM_ATTR coolantPulse() {
  if(digitalRead(Counter_3)) { //If High
    coolant_tmstp = micros();
  }
  else {
    coolant_deltaTime =(uint16_t)(micros()-coolant_tmstp); //If LOW
  }
}
void senseCoolant() {
  //coolant_raw = coolantDeltaTimeSMA(coolant_deltaTime)/100; //Should give the duty cycle in percents
  coolant_raw = coolant_deltaTime/100;
  coolant = (COOL_MUL/100) * coolant_raw + COOL_ADD;
  if (coolant>COOL_TRIGGER_HI) {
    overheatON = true;
  }
  else if (coolant<COOL_TRIGGER_LO) {
    overheatON = false;
  }
}
#pragma endregion