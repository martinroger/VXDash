#pragma once
#include <Arduino.h>
#include <stateVars.h>
#include <pinsDef.h>
#include <utils.h>

void senseBinaryIOS() {
  //There is probably a much more elegant way to do this with some bitwise wisdom
  absON         = readAddr(1);
  //doorON        = readAddr(2);
  coolantON     = readAddr(3);
  //buttonON      = readAddr(4);
  MILON         = readAddr(5);
  airbagON      = readAddr(6);
  oilON         = readAddr(7);
  parkingON     = readAddr(8);
  brakesON      = readAddr(9);
  alternatorON  = readAddr(10);
  turnON        = (readAddr(11) || readAddr(12));
  fullbeamsON   = readAddr(13);
  //backlightON   = readAddr(14);
  //ignitionON    = readAddr(15);
}