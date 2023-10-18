// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "xxxxxxxxxxxxx"
#define BLYNK_DEVICE_NAME           "IVN Project"
//#define BLYNK_AUTH_TOKEN "xxxxxxxxxxxxxxxxxx"
#define BLYNK_FIRMWARE_VERSION        "0.1.0"

#define BLYNK_PRINT Serial
//#define BLYNK_DEBUG

#define APP_DEBUG

// Uncomment your board, or configure a custom board in Settings.h
//#define USE_WROVER_BOARD
//#define USE_TTGO_T7
//#define USE_ESP32C3_DEV_MODULE
//#define USE_ESP32S2_DEV_KIT

#include "BlynkEdgent.h"
#include <Wire.h>

#define SDA1 21
#define SCL1 22
#define SDA2 18
#define SCL2 19

TwoWire I2Cone = TwoWire(0);
TwoWire I2Ctwo = TwoWire(1);

String Data,temperature,humidity,pressure,acceleration,breaking,oversteer,collision,rollover,temp,hum,pres,magnet,Data1,lattitude,Longitude,Speed;

void setup() 
{
  I2Cone.begin(SDA1,SCL1,100000);
  I2Ctwo.begin(SDA2,SCL2,100000);
  Serial.begin(115200);
  BlynkEdgent.begin();
}

void loop() 
{
  
I2Cone.requestFrom(9, 28);
Data="";
while (I2Cone.available()) {  
Data +=(char)I2Cone.read();
}

I2Ctwo.requestFrom(8, 20);
Data1="";
while (I2Ctwo.available()){
Data1 +=(char)I2Ctwo.read();  
}

Serial.println(Data);
temperature = Data.substring(0,5);
Serial.println(temperature);
humidity = Data.substring(5,10);
Serial.println(humidity);
pressure = Data.substring(10,16);
Serial.println(pressure);
acceleration = Data.substring(16,18);
Serial.println(acceleration);
breaking = Data.substring(18,20);
Serial.println(breaking);
oversteer = Data.substring(20,22);
Serial.println(oversteer);
collision = Data.substring(22,23);
Serial.println(collision);
rollover = Data.substring(23,24);
Serial.println(rollover);
temp = Data.substring(24,25);
Serial.println(temp);
hum = Data.substring(25,26);
Serial.println(hum);
pres = Data.substring(26,27);
Serial.println(pres);
magnet = Data.substring(27,28);
Serial.println(magnet);

Serial.println(Data1);
lattitude = Data1.substring(0,9);
Longitude = Data1.substring(9,18);
Speed = Data1.substring(18,20); 

if(lattitude <= 0.00)
{
lattitude = 12.9720297;  
}
else
{
  lattitude = lattitude;
}
if(Longitude <= 0.00)
{
Longitude = 79.1574943;  
}
else
{
Longitude = Longitude;  
}
Blynk.virtualWrite(V0, temperature);
Blynk.virtualWrite(V1, humidity);
Blynk.virtualWrite(V2, pressure);
Blynk.virtualWrite(V3, acceleration);
Blynk.virtualWrite(V4, breaking);
Blynk.virtualWrite(V5, oversteer);
Blynk.virtualWrite(V6, collision);
Blynk.virtualWrite(V7, rollover);
Blynk.virtualWrite(V8, temp);
Blynk.virtualWrite(V9, hum);
Blynk.virtualWrite(V10, pres);
Blynk.virtualWrite(V11, magnet);
Blynk.virtualWrite(V12, lattitude);
Blynk.virtualWrite(V13, Longitude);
Blynk.virtualWrite(V14, Speed);
Blynk.virtualWrite(V15, Longitude, lattitude);

BlynkEdgent.run();
delay(1000);
}
