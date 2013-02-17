/*
#include <Metro.h>
Metro SensorCycle = Metro(1000,1);
*/

int Joy[4];
int JoyIndx=0;
int Dummy; // Dummy buffer for analog reading
int led = 13;

//-----------------------------------------------------------------------------      

void setup()
{
    
  Serial.begin(57600); 
  pinMode(led, OUTPUT);   // LED
}

//-----------------------------------------------------------------------------      

void loop()
{  
  // if (SensorCycle.check() == 1) {TxData();}   // Sensor reading
  
  Joystick();
  
  if (Serial.available() > 0)
  {
    if(RxData(100, 1))
    {
      TxData();
      //digitalWrite(led, !digitalRead(led));  // toggle state
    }
  }
}

