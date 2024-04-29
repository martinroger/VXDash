#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogR4() {
  uint16_t val = 4095;
  val = analogRead(ADC_10);
  //analogR4 = map(val,0,4095,0,100);
  analogR4 = val;
  //Normally interpolation data goes here
}