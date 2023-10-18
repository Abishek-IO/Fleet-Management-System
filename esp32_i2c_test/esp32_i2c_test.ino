#include <Wire.h>
String Data;
void setup() 
{
  Wire.begin(9); 
  Serial.begin(115200);
  Wire.onReceive(receiveEvent);
}
void loop() 
{
  Serial.println(Data);
}
void receiveEvent(int howMany) 
{
  Data="";
  while (Wire.available()) {  
  Data +=(char)Wire.read();       
}
}
