#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogR4() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_10);
  //analogR4 = map(val,0,4095,0,100);
  analogR4 = val;
  //Normally interpolation data goes here
}