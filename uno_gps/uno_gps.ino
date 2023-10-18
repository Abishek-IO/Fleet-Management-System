#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial gpsSerial(8,9);
TinyGPSPlus gps;
double lattitude,longitude;
int Speed,altitude,satellites;
void setup() {

 gpsSerial.begin(9600);
 Serial.begin(9600);
  
  }

void loop()
{
  while (gpsSerial.available())
  {
    int data = gpsSerial.read();
    if (gps.encode(data))
    {
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      Speed = (gps.speed.kmph());
      altitude = (gps.altitude.meters());
      satellites = (gps.satellites.value());

      Serial.print ("lattitude: ");
      Serial.println (lattitude,6);
      Serial.print ("longitude: ");
      Serial.println (longitude,6);
      Serial.print ("Speed: ");
      Serial.println (Speed);
      Serial.print ("altitude: ");
      Serial.println (altitude);
      Serial.print ("No. of Satellites: ");
      Serial.println (satellites);
      
      
    }
  }
}
