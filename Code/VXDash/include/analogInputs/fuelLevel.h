#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>

void senseFuelLevel() {
  uint16_t val = 4095;
  val = analogRead(ADC_1);
  fuelLevel = map(val,0,4095,0,100);
  fuel_raw = val;
  if (fuelLevel<10) {
    lowFuelON = true; 
    }
    else if (fuelLevel>20) {
      lowFuelON = false;
    }
  //Normally interpolation data goes here
}