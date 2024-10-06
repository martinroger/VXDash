#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogR2() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_8);
  //analogR2 = map(val,0,4095,0,100);
  analogR2 = val;
  //Normally interpolation data goes here
}