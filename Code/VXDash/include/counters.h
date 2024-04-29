#pragma once
#include <Arduino.h>
#include <Arduino_Helpers.h>
#include <AH/Timing/MillisMicrosTimer.hpp>
#include <AH/STL/cmath>
#include <Filters/SMA.hpp>
#include <pinsDef.h>
#include <stateVars.h>

//Speed sensing
#pragma region 
volatile uint16_t speedPulseCounter = 0;  //Counter of pulses
SMA<10,uint16_t,uint16_t> speedPulseSMA = {0};
void IRAM_ATTR speedPulse() {
  speedPulseCounter++;
}
void senseSpeed() {
  //p_speed_raw = speed_raw;
  //p_speed = speed;
  speed_raw = speedPulseSMA(10*speedPulseCounter);
  speedPulseCounter = 0;
  speed = speed_raw * 0.24455;
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
  rpm = rpm_raw * 30;
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
  coolant = 0.7147 * coolant_raw + 63.83;
  if (coolant>100) {
    overheatON = true;
  }
  else if (coolant<95) {
    overheatON = false;
  }
}
#pragma endregion