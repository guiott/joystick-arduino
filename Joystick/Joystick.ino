#include <Bounce.h>

/*
#include <Metro.h>
Metro SensorCycle = Metro(1000,1);
*/

int Joy[4];
int JoyIndx=0;
int Dummy; // Dummy buffer for analog reading
int led = 13;
int LedR= 10;
int LedG= 9;
int LedY= 11;
int Switch=12;
int Push=8;
int LedGlight=0;
boolean SwitchOk=0;
boolean PushOk=0;
Bounce SwitchBounce = Bounce (Switch, 25);
Bounce PushBounce = Bounce (Push, 25);

//-----------------------------------------------------------------------------      

void setup()
{
    
  Serial.begin(57600); 
  pinMode(led, OUTPUT);   // LED
  pinMode(LedR, OUTPUT);  // LED red
  pinMode(LedG, OUTPUT);  // LED green
  pinMode(LedY, OUTPUT);  // LED yellow
  pinMode(Switch, INPUT);// bistable switch
  pinMode(Push, INPUT);  // momentary push button 
}

//-----------------------------------------------------------------------------      

void loop()
{  
  // if (SensorCycle.check() == 1) {TxData();}   // Sensor reading
  SwitchBounce.update();
  PushBounce.update();
  
  Joystick();
  if (Serial.available() > 0)
  {
    if(RxData(100, 1))
    {
      TxData();
      digitalWrite(LedY, !digitalRead(LedY));  // toggle state
    }
  }
  LedGlight = abs(255-(Joy[0] >> 1));
  analogWrite(LedG, (LedGlight));
  SwitchOk = SwitchBounce.read();
  PushOk = !PushBounce.read();
  digitalWrite(LedR, SwitchOk | PushOk); 
}

