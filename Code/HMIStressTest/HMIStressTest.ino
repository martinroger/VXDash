#include "EasyNextionLibrary.h"

EasyNex Nex7(Serial1);

unsigned short period = 100; //Refresh period
unsigned long lastRefreshed = 0; //last screen refresh

u_int16_t speed = 0;
u_int16_t rpm = 0;

u_int8_t fuelLevel = 0;
u_int8_t coolant = 0;
u_int8_t analogV1 = 0;
u_int8_t analogV2 = 0;
u_int8_t analogV3 = 0;
u_int8_t analogV4 = 0;
u_int8_t analogR1 = 0;
u_int8_t analogR2 = 0;
u_int8_t analogR3 = 0;
u_int8_t analogR4 = 0;
u_int8_t analogKR1 = 0;

bool lowFuelON = false;
bool oilON = false;
bool fullbeamsON = false;
bool coolantON = false;
bool MILON = false;
bool turnON = false;
bool parkingON = false;
bool absON = false;
bool brakesON = false;
bool overheatON = false;
bool airbagON = false;
bool alternatorON = false;

void setup() {
  // put your setup code here, to run once:
Nex7.begin(512000);
Nex7.writeNum("period.val",period);

}

void loop() {
  Nex7.NextionListen();
  // Periodically force feed the screen
  if((millis()-lastRefreshed)>period) {
    lastRefreshed = millis();
    refreshScreen();
  }
  generateRandomSignals();

}

void refreshScreen() {

}

void generateRandomSignals() {

}