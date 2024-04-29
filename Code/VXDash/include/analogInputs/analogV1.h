#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogV1() {
  uint16_t val = 4095;
  val = analogRead(ADC_3);
  //analogV1 = map(val,0,4095,0,100);
  analogV1 = val;
  //Normally interpolation data goes here
}