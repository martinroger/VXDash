#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogKR1() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_11);
  //analogKR1 = map(val,0,4095,0,100);
  analogKR1 = val;
  //Normally interpolation data goes here
}