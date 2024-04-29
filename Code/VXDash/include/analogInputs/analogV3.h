#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogV3() {
  uint16_t val = 4095;
  val = analogRead(ADC_5);
  //analogV3 = map(val,0,4095,0,100);
  analogV3 = val;
  //Normally interpolation data goes here
}