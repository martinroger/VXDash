#pragma once
#include <pinsDef.h>
#include <Arduino.h>
#include <stateVars.h>

bool readAddr(int addr) {
  digitalWrite(S0,bitRead(addr,0));
  digitalWrite(S1,bitRead(addr,1));
  digitalWrite(S2,bitRead(addr,2));
  digitalWrite(S3,bitRead(addr,3));
  return !digitalRead(COM);
}

void generateRandomSignals() {
  //int hallVal = hallRead(); //Could be used to stimulate externally ?
  speed       = floor(300*(0.5+0.5*sin(millis()*(2*PI)/15000)));
  rpm         = floor(8000*(0.5+0.5*sin(millis()*(2*PI)/3000)));
  fuelLevel   = floor(100*(0.5+0.5*sin(millis()*(2*PI)/30000)));
  coolant     = floor(130*(0.5+0.5*sin(millis()*(2*PI)/20000)));
  analogV1    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/1000)));
  analogV2    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/2000)));
  analogV3    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/3000)));
  analogV4    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/4000)));
  analogR1    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/1500)));
  analogR2    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/3000)));
  analogR3    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/4500)));
  analogR4    = floor(100*(0.5+0.5*sin(millis()*(2*PI)/6000)));
  analogKR1   = floor(100*(0.5+0.5*sin(millis()*(2*PI)/2222)));

  lowFuelON = (bool)(round(random(0,101)/100));
  oilON = (bool)(round(random(0,101)/100));
  fullbeamsON = (bool)(round(random(0,101)/100));
  coolantON = (bool)(round(random(0,101)/100));
  MILON = (bool)(round(random(0,101)/100));
  turnON = (bool)(round(random(0,101)/100));
  parkingON = (bool)(round(random(0,101)/100));
  absON = (bool)(round(random(0,101)/100));
  brakesON = (bool)(round(random(0,101)/100));
  overheatON = (bool)(round(random(0,101)/100));
  airbagON = (bool)(round(random(0,101)/100));
  alternatorON = (bool)(round(random(0,101)/100));
}