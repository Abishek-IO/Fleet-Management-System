#include <SoftwareSerial.h>
#include <TinyGPS++.h>
#include<Wire.h>

SoftwareSerial gpsSerial(4,3);
TinyGPSPlus gps;

double lattitude,Longitude;
int Speed;
String latdata,longdata,speeddata,padding="0",combine;

void setup() {
  gpsSerial.begin(9600);
  Serial.begin(9600);
  Wire.begin(8);
  Wire.onRequest(requestEvent);
  Serial.println("GPS Sender");
}

void loop() 
{ 
  while (gpsSerial.available()){
  int data = gpsSerial.read();
  if(gps.encode(data))
    {
      lattitude = (gps.location.lat());
      Longitude = (gps.location.lng());
      Speed = (gps.speed.kmph());

      Serial.print ("lattitude: ");
      Serial.println (lattitude,6);
      Serial.print ("longitude: ");
      Serial.println (Longitude,6);
      Serial.print ("Speed: ");
      Serial.println (Speed);
 
  if(lattitude == 0.000000)
  {
    latdata = "12.972029";
  }
  else
  {
    latdata = String(lattitude,6);
  }
  if(Longitude == 0.000000)
  {
    longdata = "79.157494";
  }
  else
  {
    longdata = String(Longitude,6);
  }
  if(Speed<10)
  {
    speeddata = padding+String(Speed);
  }
  else
  {
    speeddata = String(Speed);
  }
  combine = latdata+longdata+speeddata;
  delay(1000);  
    }
  }  
}
void requestEvent()
{
  Wire.write(combine.c_str());         
}
