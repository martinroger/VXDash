#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogV2() {
  uint16_t val = 4095;
  val = analogRead(ADC_4);
  //analogV2 = map(val,0,4095,0,100);
  analogV2 = val;
  //Normally interpolation data goes here
}