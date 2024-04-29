#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseAnalogKR1() {
  uint16_t val = 4095;
  val = analogRead(ADC_11);
  //analogKR1 = map(val,0,4095,0,100);
  analogKR1 = val;
  //Normally interpolation data goes here
}