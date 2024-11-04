#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogV4() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_6);
  //analogV4 = map(val,0,4095,0,100);
  analogV4 = val;
  //Normally interpolation data goes here
}