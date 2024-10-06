#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogV2() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_4);
  //analogV2 = map(val,0,4095,0,100);
  analogV2 = val;
  //Normally interpolation data goes here
}