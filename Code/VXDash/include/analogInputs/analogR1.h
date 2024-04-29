#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogR1() {
  uint16_t val = 4095;
  val = analogRead(ADC_7);
  //analogR1 = map(val,0,4095,0,100);
  analogR1 = val;
  //Normally interpolation data goes here
}