int dutyCycle = 0;
int potRead = 0;
unsigned long highDuration = 0;
unsigned long lowDuration = 0;
unsigned long lastChange = 0;
bool PWMon = true;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN,OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
  potRead = analogRead(A0);
  dutyCycle = map(potRead,0,1023,0,100);
  highDuration = map(dutyCycle,0,100,0,10000);
  lowDuration = 10000-highDuration;
  if((PWMon)) {
    if((micros()-lastChange)>highDuration) {
      digitalWrite(LED_BUILTIN,LOW);
      PWMon = false;
      lastChange = micros();
    }
  }
  else {
    if((micros()-lastChange)>lowDuration) {
      digitalWrite(LED_BUILTIN,HIGH);
      PWMon = true;
      lastChange = micros();
    }
  }

}
