//Required for communication with the Serial Nextion screen. Provides an easy wrapper as well as some interrupts.
#include "EasyNextionLibrary.h" 
#include "pinsDef.h"
#include "utils.h"
#include <Arduino_Helpers.h>
#include <AH/Timing/MillisMicrosTimer.hpp>
#include <AH/STL/cmath>
#include <Filters/SMA.hpp>
#include <counters.h>
#include <stateVars.h>
#include <muxSense.h>
#include <analogs.h>

//useful debug flag, can also be triggered via the screen
bool debugFlag = false;

//Nextion screen instance on Serial 2 (GPIO 16 and 17)
EasyNex Nex7(Serial2);

//Instancing the main screen refresh Timer
Timer<millis> screenTimer = 60;
Timer<millis> slowRefresh = 500;
Timer<millis> fastRefresh = 100;

void refreshScreen() {
  //Checks for value change, only refreshes in that case
  if(speed!=p_speed) {
    Nex7.writeNum("speed.val",speed);
    p_speed=speed;
  }
  if(speed_raw!=p_speed_raw) {
    Nex7.writeNum("speed_raw.val",speed_raw);
    p_speed_raw=speed_raw;
  }
  if(rpm!=p_rpm) {
    Nex7.writeNum("rpm.val",rpm);
    p_rpm=rpm;
  }
  if(rpm_raw!=p_rpm_raw) {
    Nex7.writeNum("rpm_raw.val",rpm_raw);
    p_rpm_raw=rpm_raw;
  }
  if(fuelLevel!=p_fuelLevel) {
    Nex7.writeNum("fuelLevel.val",fuelLevel);
    p_fuelLevel=fuelLevel;
  }
  if(fuel_raw!=p_fuel_raw) {
    Nex7.writeNum("fuel_raw.val",fuel_raw);
    p_fuel_raw=fuel_raw;
  }
  if(coolant!=p_coolant) {
    Nex7.writeNum("coolant.val",coolant);
    p_coolant=coolant;
  }
  if(coolant_raw!=p_coolant_raw) {
    Nex7.writeNum("coolant_raw.val",coolant_raw);
    p_coolant_raw=coolant_raw;
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
    Nex7.writeNum("analogKR1.val",analogKR1);
    p_analogKR1=analogKR1;
  }
  if(lowFuelON!=p_lowFuelON) {       
    Nex7.writeNum("lowFuelON.aph",127*((int)lowFuelON)); //uses a multiplication with the icon alpha
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

//Nextion trigger for debug
void trigger0() {
  debugFlag = !debugFlag;
}

void setup() {
  if(debugFlag) { //Purely for debug, open a Serial port over USB if enabled
    Serial.begin(112500);
    randomSeed(millis());
  } 
  //Start Nextion screen Serial
  Nex7.begin(921600);

  //Declare pin types for the MUX
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(COM,INPUT);

  //Setup counters and IRQs
  #pragma region
  pinMode(Counter_1,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Counter_1),rpmPulse,RISING);

  pinMode(Counter_2,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Counter_2),speedPulse,RISING);

  pinMode(Counter_3,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Counter_3),coolantPulse,CHANGE);
  #pragma endregion
}

void loop() {
  Nex7.NextionListen();
  // Periodically force feed the screen
  if(screenTimer) refreshScreen();
  
  //If the debugflag is on, use random values
  if(debugFlag) {
    generateRandomSignals();
  }
  else {
    if(slowRefresh) {
      senseAnalogV1();
      senseAnalogV2();
      senseAnalogV3();
      senseAnalogV4();
      senseAnalogR1();
      senseAnalogR2();
      senseAnalogR3();
      senseAnalogR4();
      senseAnalogKR1();
      senseFuelLevel();
      senseCoolant();
    }
    if(fastRefresh) {
      senseBinaryIOS();
      senseSpeed();
      senseRPM();
    }
  }
}