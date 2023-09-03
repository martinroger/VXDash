//Required for communication with the Serial Nextion screen. Provides an easy wrapper as well as some interrupts.
#include "EasyNextionLibrary.h" 
//Requires EmotiBit ArduinoFilters to add some filters and tasteful timers
#include <Arduino_Helpers.h>
#include <AH/Timing/MillisMicrosTimer.hpp>

//useful debug flag, can also be triggered via the screen
bool debugFlag = false;

//Just to help correspondance with the schematic
const int S0        = 12;
const int S1        = 0;
const int S2        = 2;
const int S3        = 15;
const int COM       = 21;
const int ADC_1     = 36;
const int ADC_3     = 34;
const int ADC_4     = 35;
const int ADC_5     = 32;
const int ADC_6     = 33;
const int ADC_7     = 25;
const int ADC_8     = 26;
const int ADC_9     = 27;
const int ADC_10    = 14;
const int ADC_11    = 13;
const int Counter_1 = 23; //RPM
const int Counter_2 = 22; //SPEED
const int Counter_3 = 39; //Water temp
const int Digital_1 = 19;
const int Digital_2 = 18;
const int Digital_3 = 5;
const int Digital_4 = 4;

//Nextion screen instance on Serial 2 (GPIO 16 and 17)
EasyNex Nex7(Serial2);

//Instancing the main screen refresh Timer
Timer<millis> screenTimer = 60;
Timer<millis> slowRefresh = 500;
Timer<millis> fastRefresh = 100;

// p_ variables are meant for limiting refresh attempts
uint16_t speed = 0;           //Last calculated value
uint16_t p_speed = 0;         //Previous refresh value
uint16_t speed_raw = 0;       //Last raw value (PPS)
uint16_t p_speed_raw = 0;     //Previous raw value (PPS)
volatile uint32_t tmstp_speed = 0;     //Last pulse timestamp
volatile uint32_t intv_speed = 300000; //Pulse intervals duration
uint16_t rpm = 0;
uint16_t p_rpm = 0;
uint16_t rpm_raw = 0;
uint16_t p_rpm_raw = 0;
volatile uint32_t tmstp_rpm = 0;
volatile uint32_t intv_rpm = 0;

uint8_t fuelLevel = 0;
uint16_t fuel_raw = 0;
uint8_t coolant = 0;
uint16_t coolant_raw = 0;
uint16_t analogV1 = 0;
uint16_t analogV2 = 0;
uint16_t analogV3 = 0;
uint16_t analogV4 = 0;
uint16_t analogR1 = 0;
uint16_t analogR2 = 0;
uint16_t analogR3 = 0;
uint16_t analogR4 = 0;
uint16_t analogKR1 = 0;

uint8_t p_fuelLevel = 0;
uint16_t p_fuel_raw = 0;
uint8_t p_coolant = 0;
uint16_t p_coolant_raw = 0;
uint16_t p_analogV1 = 0;
uint16_t p_analogV2 = 0;
uint16_t p_analogV3 = 0;
uint16_t p_analogV4 = 0;
uint16_t p_analogR1 = 0;
uint16_t p_analogR2 = 0;
uint16_t p_analogR3 = 0;
uint16_t p_analogR4 = 0;
uint16_t p_analogKR1 = 0;

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
  if(debugFlag) { //Purely for debug, open a Serial port over USB if enabled
    Serial.begin(112500);
    randomSeed(millis());
  } 

  Nex7.begin(921600);

  //Declare pin types for the MUX
  pinMode(S0,OUTPUT);
  pinMode(S1,OUTPUT);
  pinMode(S2,OUTPUT);
  pinMode(S3,OUTPUT);
  pinMode(COM,INPUT);

  pinMode(Counter_1,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Counter_1),rpmPulse,RISING);

  pinMode(Counter_2,INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(Counter_2),speedPulse,RISING);

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

void senseAnalogV1() {
  uint16_t val = 4095;
  val = analogRead(ADC_3);
  //analogV1 = map(val,0,4095,0,100);
  analogV1 = val;
  //Normally interpolation data goes here
}
void senseAnalogV2() {
  uint16_t val = 4095;
  val = analogRead(ADC_4);
  //analogV2 = map(val,0,4095,0,100);
  analogV2 = val;
  //Normally interpolation data goes here
}
void senseAnalogV3() {
  uint16_t val = 4095;
  val = analogRead(ADC_5);
  //analogV3 = map(val,0,4095,0,100);
  analogV3 = val;
  //Normally interpolation data goes here
}
void senseAnalogV4() {
  uint16_t val = 4095;
  val = analogRead(ADC_6);
  //analogV4 = map(val,0,4095,0,100);
  analogV4 = val;
  //Normally interpolation data goes here
}

void senseAnalogR1() {
  uint16_t val = 4095;
  val = analogRead(ADC_7);
  //analogR1 = map(val,0,4095,0,100);
  analogR1 = val;
  //Normally interpolation data goes here
}
void senseAnalogR2() {
  uint16_t val = 4095;
  val = analogRead(ADC_8);
  //analogR2 = map(val,0,4095,0,100);
  analogR2 = val;
  //Normally interpolation data goes here
}
void senseAnalogR3() {
  uint16_t val = 4095;
  val = analogRead(ADC_9);
  //analogR3 = map(val,0,4095,0,100);
  analogR3 = val;
  //Normally interpolation data goes here
}
void senseAnalogR4() {
  uint16_t val = 4095;
  val = analogRead(ADC_10);
  //analogR4 = map(val,0,4095,0,100);
  analogR4 = val;
  //Normally interpolation data goes here
}

void senseAnalogKR1() {
  uint16_t val = 4095;
  val = analogRead(ADC_11);
  //analogKR1 = map(val,0,4095,0,100);
  analogKR1 = val;
  //Normally interpolation data goes here
}

void senseSpeed() {
  unsigned long interval = 300001;
  unsigned long timestamp = 0;
  p_speed_raw = speed_raw;
  p_speed = speed;
  noInterrupts();
  interval = intv_speed;
  timestamp = tmstp_speed;
  interrupts();
  interval = max(interval,(micros()-timestamp));
  if(interval > 300000) {
    speed = 0;
    speed_raw = 0;
  }
  else {
    speed_raw = 1000000/interval;
    speed = speed_raw / 5; //Probably would need some care there
  }
}
void senseRPM() {
  unsigned long interval = 100001;
  unsigned long timestamp = 0;
  p_rpm_raw = rpm_raw;
  p_rpm = rpm;
  noInterrupts();
  interval = intv_rpm;
  timestamp = tmstp_rpm;
  interrupts();
  interval = max(interval,(micros()-timestamp));
  if(interval > 100000) {
    rpm = 0;
    rpm_raw = 0;
  }
  else {
    rpm_raw = 1000000/interval;
    rpm = rpm_raw*30;
  }
}
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
void senseCoolant() {
  if(!debugFlag) {
    coolant = floor(130*(0.5+0.5*sin(millis()*(2*PI)/20000)));
  }
  if (coolant>100) {
    overheatON = true;
  }
  else if (coolant<95) {
    overheatON = false;
  }
}

bool readAddr(int addr) {
  digitalWrite(S0,bitRead(addr,0));
  digitalWrite(S1,bitRead(addr,1));
  digitalWrite(S2,bitRead(addr,2));
  digitalWrite(S3,bitRead(addr,3));
  return !digitalRead(COM);
}

void trigger0() {
  debugFlag = !debugFlag;
}

void speedPulse() {
  intv_speed = micros()-tmstp_speed;
  tmstp_speed = micros();
}

void rpmPulse() {
  intv_rpm = micros()-tmstp_rpm;
  tmstp_rpm = micros();
}