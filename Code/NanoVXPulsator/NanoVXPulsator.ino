/*
Potentiometers (1K or more) connected to A0 A1 A2 qnd A3
Outputs are on D2 D3 and D13
Mapping as follows:
D2 -> Speed 
D3 -> RPM
D13 -> Water temp PWM
A0 duty cycle for D2 and D3
A1 Speed freq
A2 RPM freq
A3 Duty cycle Water T
*/

#include <smart_duty_cycling.h>

smart_duty_cycling speedCycle;
smart_duty_cycling rpmCycle;
smart_duty_cycling water_TCycle;
smart_duty_cycling potCycle;
float pot_freq = 10.0;
float speed_freq = 1.0;
float rpm_freq = 1.0;
float gen_duty_cycle = 0.25;
float water_T_duty_cycle = 0.1;
int rawA0 = 0;
int rawA1 = 0;
int rawA2 = 0;
int rawA3 = 0;


void setup() {
  //Serial.begin(115200);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(13,OUTPUT);

  speedCycle.setFrequencyDutyCycle(speed_freq,gen_duty_cycle);
  rpmCycle.setFrequencyDutyCycle(rpm_freq,gen_duty_cycle);
  water_TCycle.setFrequencyDutyCycle(100.0,water_T_duty_cycle);
  potCycle.setFrequencyDutyCycle(pot_freq,0.5);
  //Serial.println("Setup Done");
}

void loop() {
  //Refresh the pot readouts
  if(potCycle.switchMode()) {
    if(potCycle.wake) {
      rawA0 = analogRead(A0); //generate DC
      //Serial.print(rawA0); Serial.print(" ");
      rawA1 = analogRead(A1); //Speed
      //Serial.print(rawA1); Serial.print(" ");
      rawA2 = analogRead(A2); //RPM
      //Serial.print(rawA2); Serial.print(" ");
      rawA3 = analogRead(A3); //Water
      //Serial.println(rawA3);
      
      //gen_duty_cycle = ((float)map(rawA0,0,1023,10,95))/100.0;
      //gen_duty_cycle = constrain(gen_duty_cycle,0.2,0.8);

      speed_freq = (float)map(rawA1,0,1023,0,987);
      speed_freq = constrain(speed_freq,0.01,987.0);
      speedCycle.setFrequencyDutyCycle(speed_freq,gen_duty_cycle);

      rpm_freq = ((float)map(rawA2,0,1023,0,14000))/60.0;
      rpm_freq = constrain(rpm_freq,0.01,240);
      rpmCycle.setFrequencyDutyCycle(rpm_freq,gen_duty_cycle);

      water_T_duty_cycle = ((float)map(rawA3,0,1023,10,95))/100.0;
      water_T_duty_cycle = constrain(water_T_duty_cycle,0.1,0.95);
      water_TCycle.setDutyCycle(water_T_duty_cycle);
    }
  }


  if(water_TCycle.switchMode()) {
    if(water_TCycle.wake) {
      digitalWrite(13,HIGH);
    }
    else
    {
      digitalWrite(13,LOW);
    }
  }

  if(speedCycle.switchMode()) {
    if(speedCycle.wake) {
      digitalWrite(2,HIGH);
    }
    else digitalWrite(2,LOW);
  }

  if(rpmCycle.switchMode()) {
    if(rpmCycle.wake) {
      digitalWrite(3,HIGH);
    }
    else digitalWrite(3,LOW);
  }
}
