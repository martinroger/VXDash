#pragma once
#include <Arduino.h>
#include <Arduino_Helpers.h>
#include <Filters/SMA.hpp>
#include <stateVars.h>
#include <pinsDef.h>

SMA<100,uint8_t,uint16_t> fuelLevelSMA = {0};

void senseFuelLevel() {
  uint32_t val = 0;
  uint8_t tempLevel = 0;
  val = analogReadMilliVolts(ADC_1);
  tempLevel = map(val,150,3100,0,100);
  fuelLevel = fuelLevelSMA(tempLevel);
  fuel_raw = val;
  if (fuelLevel<10) {
    lowFuelON = true; 
    }
    else if (fuelLevel>20) {
      lowFuelON = false;
    }
  //Normally interpolation data goes here
}