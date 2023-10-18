// Copyright (c) Sandeep Mistry. All rights reserved.
// Licensed under the MIT license. See LICENSE file in the project root for full license information.

#include <CAN.h>
#include <SoftwareSerial.h>
#include <TinyGPS++.h>
SoftwareSerial gpsSerial(12,13);
TinyGPSPlus gps;
double lattitude,longitude;
double Speed,Altitude,Satellites;
char Lat[9],Long[9],Speed1[6],Altitude1[7],Satellites1[6];

void setup() {
  gpsSerial.begin(9600);
  Serial.begin(115200);
  Serial.println("CAN Sender");

  // start the CAN bus at 500 kbps
  if (!CAN.begin(500E3)) {
    Serial.println("Starting CAN failed!");
    while (1);
  }
}

void loop() {
  // send packet: id is 11 bits, packet can contain up to 8 bytes of data
  while (gpsSerial.available()>0)
  {
    gps.encode(gpsSerial.read());
    if (gps.location.isUpdated())
    {
      lattitude = (gps.location.lat());
      longitude = (gps.location.lng());
      Speed = (gps.speed.kmph());
      Altitude = (gps.altitude.meters());
      Satellites = (gps.satellites.value());

      Serial.print ("lattitude: ");
      Serial.println (lattitude,5);
      Serial.print ("longitude: ");
      Serial.println (longitude,5);
      Serial.print ("Speed: ");
      Serial.println (Speed);
      Serial.print ("altitude: ");
      Serial.println (Altitude);
      Serial.print ("No. of Satellites: ");
      Serial.println (Satellites); 
      }
  }

                 dtostrf(lattitude,7,5,Lat);
      dtostrf(longitude,7,5,Long);
      dtostrf(Speed,2,0,Speed1);
      dtostrf(Altitude,3,0,Altitude1);   
      dtostrf(Satellites,2,0,Satellites1);
     
      Serial.println(Lat);
      Serial.println(Long);
      Serial.println(Speed1);
      Serial.println(Altitude1);
      Serial.println(Satellites1);
      delay(500);
  
  Serial.println("Sending Lattitude packet ... ");
  CAN.beginPacket(0x10);
  CAN.write(Lat[0]);
  CAN.write(Lat[1]);
  CAN.write(Lat[2]);
  CAN.write(Lat[3]);
  CAN.write(Lat[4]);
  CAN.write(Lat[5]);
  CAN.write(Lat[6]);
  CAN.write(Lat[7]);
  CAN.endPacket();
  Serial.println("done");
  delay(500);

  Serial.println("Sending Longitude packet ... ");
  CAN.beginPacket(0x11);
  CAN.write(Long[0]);
  CAN.write(Long[1]);
  CAN.write(Long[2]);
  CAN.write(Long[3]);
  CAN.write(Long[4]);
  CAN.write(Long[5]);
  CAN.write(Long[6]);
  CAN.write(Long[7]);
  CAN.endPacket();
  Serial.println("done");
  delay(500);
  
  Serial.println("Sending Speed packet ... ");  
  CAN.beginPacket(0x12);
  CAN.write(Speed1[0]);
  CAN.write(Speed1[1]);
  CAN.endPacket();
  Serial.println("done");
  delay(500);
  
  Serial.println("Sending Altitude packet ... ");
  CAN.beginPacket(0x13);
  CAN.write(Altitude1[0]);
  CAN.write(Altitude1[1]);
  CAN.write(Altitude1[2]);
  CAN.endPacket();
  Serial.println("done");
  delay(500);
  
  Serial.println("Sending Satellites packet ... ");
  CAN.beginPacket(0x14);
  CAN.write(Satellites1[0]);
  CAN.write(Satellites1[1]);
  CAN.endPacket();
  Serial.println("done");
  delay(500);
}
