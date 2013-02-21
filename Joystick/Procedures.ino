void TxData(void)
{
  // send sensors data on serial port
  int i;            // generic index
  byte TxBuff[16];
  byte ChkSum=0;

  TxBuff[0] = 64;  // Header = "@"
  TxBuff[1] = 0;   // broadcast
  TxBuff[2] = 100; // command = "d"
  TxBuff[3] = 12;   // command length
  TxBuff[4] = Joy[0] >> 8;
  TxBuff[5] = Joy[0];
  TxBuff[6] = Joy[1] >> 8;
  TxBuff[7] = Joy[1];
  TxBuff[8] = Joy[2] >> 8;
  TxBuff[9] = Joy[2];
  TxBuff[10] = Joy[3] >> 8;
  TxBuff[11] = Joy[3];
  
  for (i=0; i<=11; i++)
  {
    ChkSum += TxBuff[i];
    Serial.write(TxBuff[i]);
  }
 
  Serial.write(ChkSum);

  for(i=0; i<4; i++)
  {
    Joy[i]=0;
  }
  
}

boolean RxData(byte Cmd, byte Len)
{// receive data on serial port 
  static int i = 0;            // generic index
  static byte RxBuff[16];
  byte ChkSum=0;
  
  // get incoming byte:
  RxBuff[i] = Serial.read();
  
  if( i == (3 + Len))
  {
   if (RxBuff[0] != '@')
      {
        RxError(2, Cmd, Len, ChkSum);
        i = 0;
        return false;
      }
      else if (RxBuff[2] != Cmd)
      {
        RxError(3, Cmd, Len, ChkSum);
        i = 0;
        return false;
      }
      else if (RxBuff[3] != (Len))
      {
        RxError(4, Cmd, Len, ChkSum);
        i = 0;        
        return false;
      }
      
      for (i=0; i < (3 + Len); i++)  //  ChkSum excluded
      {
        ChkSum += (char)(RxBuff[i]);
      }
      ChkSum = ChkSum % 256;
      
      if (RxBuff[i] != ChkSum)
      {
        RxError(5, Cmd, Len, ChkSum);
        i = 0;
        return false;
      }
  }
  else
  {
    i++;
    return false;
  }
  
  i = 0;
  return true;
}

void RxError(int ErrCode, char Cmd, int Len, int ChkSum)
{
  int Dummy;
  
  digitalWrite(led, !digitalRead(led));  // toggle state

  while (Serial.available() > 0)
  { // flush RX buffer
    Dummy = Serial.read();
  }
}


void Joystick(void)
{
Joy[JoyIndx] = (Joy[JoyIndx]  + analogRead(JoyIndx)) / 2; // average
  JoyIndx ++;
  if(JoyIndx >= 4)
  {
    JoyIndx = 0;
  }
  /* Switching in advance to the next port to measure, this allows the voltage
    to stabilize to the new value on the ADC Sample/Hold
  */
  Dummy = analogRead(JoyIndx);
}
