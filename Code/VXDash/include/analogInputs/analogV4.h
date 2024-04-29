#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogV4() {
  uint16_t val = 4095;
  val = analogRead(ADC_6);
  //analogV4 = map(val,0,4095,0,100);
  analogV4 = val;
  //Normally interpolation data goes here
}