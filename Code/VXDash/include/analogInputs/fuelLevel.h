#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseFuelLevel() {
  uint32_t val = 0;
  val = analogReadMilliVolts(ADC_1);
  fuelLevel = map(val,0,3100,0,100);
  fuel_raw = val;
  if (fuelLevel<10) {
    lowFuelON = true; 
    }
    else if (fuelLevel>20) {
      lowFuelON = false;
    }
  //Normally interpolation data goes here
}