#include "EasyNextionLibrary.h"

bool debugFlag = true;

EasyNex Nex7(Serial2);

unsigned short refreshInterval = 60; //Refresh refreshInterval
unsigned long lastRefreshed = 0; //last screen refresh

u_int16_t speed = 0;
u_int16_t p_speed = 0;
u_int16_t rpm = 0;
u_int16_t p_rpm = 0;

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

u_int8_t p_fuelLevel = 0;
u_int8_t p_coolant = 0;
u_int8_t p_analogV1 = 0;
u_int8_t p_analogV2 = 0;
u_int8_t p_analogV3 = 0;
u_int8_t p_analogV4 = 0;
u_int8_t p_analogR1 = 0;
u_int8_t p_analogR2 = 0;
u_int8_t p_analogR3 = 0;
u_int8_t p_analogR4 = 0;
u_int8_t p_analogKR1 = 0;

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

bool p_lowFuelON = false;
bool p_oilON = false;
bool p_fullbeamsON = false;
bool p_coolantON = false;
bool p_MILON = false;
bool p_turnON = false;
bool p_parkingON = false;
bool p_absON = false;
bool p_brakesON = false;
bool p_overheatON = false;
bool p_airbagON = false;
bool p_alternatorON = false;

void setup() {
if(debugFlag) { //Purely for debug
  Serial.begin(112500);
  randomSeed(millis());
} 

Nex7.begin(921600);
Nex7.writeNum("period.val",refreshInterval);
}

void loop() {
  Nex7.NextionListen();
  // Periodically force feed the screen
  if((millis()-lastRefreshed)>refreshInterval) {
    lastRefreshed = millis();
    refreshScreen();
  }
  if(debugFlag) {
    generateRandomSignals();
    if(Serial.available()>0) {
      refreshInterval = Serial.parseInt(); //Fetch a new refresh rate
    }
  }
}

void refreshScreen() {
  //Checks for value change, only refreshes in that case
  Nex7.writeNum("period.val",refreshInterval);
  if(speed!=p_speed) {
    Nex7.writeNum("speed.val",speed);
    p_speed=speed;
  }
  if(rpm!=p_rpm) {
    Nex7.writeNum("rpm.val",rpm);
    p_rpm=rpm;
  }
  if(fuelLevel!=p_fuelLevel) {
    Nex7.writeNum("fuelLevel.val",fuelLevel);
    p_fuelLevel=fuelLevel;
  }
  if(coolant!=coolant) {
    Nex7.writeNum("coolant.val",coolant);
    p_coolant=coolant;
  }
  if(analogV1!=p_analogV1) {
    Nex7.writeNum("analogV1.val",analogV1);
    p_analogV1=analogV1;
  }
  if(analogV2!=p_analogV2) {
    Nex7.writeNum("analogV2.val",analogV2);
    p_analogV2=analogV2;
  }
  if(analogV3!=p_analogV3) {
    Nex7.writeNum("analogV3.val",analogV3);
    p_analogV3=analogV3;
  }
  if(analogV4!=p_analogV4) {
    Nex7.writeNum("analogV4.val",analogV4);
    p_analogV4=analogV4;
  }
  if(analogR1!=p_analogR1) {
    Nex7.writeNum("analogR1.val",analogR1);
    p_analogR1=analogR1;
  }
  if(analogR2!=p_analogR2) {
    Nex7.writeNum("analogR2.val",analogR2);
    p_analogR2=analogR2;
  }
  if(analogR3!=p_analogR3) {
    Nex7.writeNum("analogR3.val",analogR3);
    p_analogR3=analogR3;
  }
  if(analogR4!=p_analogR4) {
    Nex7.writeNum("analogR4.val",analogR4);
    p_analogR4=analogR4;
  }
  if(analogKR1!=p_analogKR1) {
    Nex7.writeNum("analogR1.val",analogKR1);
    p_analogKR1=analogKR1;
  }
  if(lowFuelON!=p_lowFuelON) {       
    Nex7.writeNum("lowFuelON.aph",127*((int)lowFuelON)); //uses a multiplication with the alpha factor
    p_lowFuelON = lowFuelON;
  }
  if(oilON!=p_oilON) {
    Nex7.writeNum("oilON.aph",127*((int)oilON));
    p_oilON=oilON;
  }
  if(fullbeamsON!=p_fullbeamsON) {
    Nex7.writeNum("fullbeamsON.aph",127*((int)fullbeamsON));
    p_fullbeamsON = fullbeamsON;
  }
  if(coolantON!=p_coolantON) {
    Nex7.writeNum("coolantON.aph",127*((int)coolantON));
    p_coolantON = coolantON;
  }
  if(MILON!=p_MILON) {
    Nex7.writeNum("MILON.aph",127*((int)MILON));
    p_MILON=MILON;
  }
  if(turnON!=p_turnON) {
    Nex7.writeNum("turnON.aph",127*((int)turnON));
    p_turnON=turnON;
  }
  if(parkingON!=p_parkingON) {
    Nex7.writeNum("parkingON.aph",127*((int)parkingON));
    p_parkingON = parkingON;
  }
  if(absON!=p_absON) {
    Nex7.writeNum("absON.aph",127*((int)absON));
    p_absON = absON;
  }
  if(brakesON!=p_brakesON) {
    Nex7.writeNum("brakesON.aph",127*((int)brakesON));
    p_brakesON=brakesON;
  }
  if(overheatON!=p_overheatON) {
    Nex7.writeNum("overheatON.aph",127*((int)overheatON));
    p_overheatON=overheatON;
  }
  if(airbagON!=p_airbagON) {
    Nex7.writeNum("airbagON.aph",127*((int)airbagON));
    p_airbagON=airbagON;
  }
  if(alternatorON!=p_alternatorON) {
    Nex7.writeNum("alternatorON.aph",127*((int)alternatorON));
    p_alternatorON=alternatorON;
  }
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

void senseBinaryIOS() {}

void senseAnalogV1() {}
void senseAnalogV2() {}
void senseAnalogV3() {}
void senseAnalogV4() {}

void senseAnalogR1() {}
void senseAnalogR2() {}
void senseAnalogR3() {}
void senseAnalogR4() {}

void senseAnalogKR1() {}

void senseSpeed() {}
void senseRPM() {}
void senseFuelLevel() {}
void senseCoolant() {}