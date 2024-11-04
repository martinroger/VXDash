#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogV1() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_3);
  //analogV1 = map(val,0,4095,0,100);
  analogV1 = val;
  //Normally interpolation data goes here
}