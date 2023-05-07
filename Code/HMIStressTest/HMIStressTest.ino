#include "EasyNextionLibrary.h"

EasyNex Nex7(Serial2);

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
Serial.begin(112500);
Nex7.begin(921600);
Nex7.writeNum("period.val",period);
randomSeed(millis());

}

void loop() {
  Nex7.NextionListen();
  // Periodically force feed the screen
  if((millis()-lastRefreshed)>period) {
    lastRefreshed = millis();
    refreshScreen();
  }
  generateRandomSignals();
  if(Serial.available()>0) {
    period = Serial.parseInt();
  }
}

void refreshScreen() {
  //Simple force refresh for maximum Serial stress
  Nex7.writeNum("period.val",period);
  Nex7.writeNum("speed.val",speed);
  Nex7.writeNum("rpm.val",rpm);
  Nex7.writeNum("fuelLevel.val",fuelLevel);
  Nex7.writeNum("coolant.val",coolant);
  Nex7.writeNum("analogV1.val",analogV1);
  Nex7.writeNum("analogV2.val",analogV2);
  Nex7.writeNum("analogV3.val",analogV3);
  Nex7.writeNum("analogV4.val",analogV4);
  Nex7.writeNum("analogR1.val",analogR1);
  Nex7.writeNum("analogR2.val",analogR2);
  Nex7.writeNum("analogR3.val",analogR3);
  Nex7.writeNum("analogR4.val",analogR4);
  Nex7.writeNum("analogKR1.val",analogKR1);
  Nex7.writeNum("lowFuelON.aph",127*((int)lowFuelON)); //uses a multiplication with the alpha factor
  Nex7.writeNum("oilON.aph",127*((int)oilON));
  Nex7.writeNum("fullbeamsON.aph",127*((int)fullbeamsON));
  Nex7.writeNum("coolantON.aph",127*((int)coolantON));
  Nex7.writeNum("MILON.aph",127*((int)MILON));
  Nex7.writeNum("turnON.aph",127*((int)turnON));
  Nex7.writeNum("parkingON.aph",127*((int)parkingON));
  Nex7.writeNum("absON.aph",127*((int)absON));
  Nex7.writeNum("brakesON.aph",127*((int)brakesON));
  Nex7.writeNum("overheatON.aph",127*((int)overheatON));
  Nex7.writeNum("airbagON.aph",127*((int)airbagON));
  Nex7.writeNum("alternatorON.aph",127*((int)alternatorON));

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