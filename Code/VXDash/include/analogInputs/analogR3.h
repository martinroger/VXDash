#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogR3() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_9);
  //analogR3 = map(val,0,4095,0,100);
  analogR3 = val;
  //Normally interpolation data goes here
}