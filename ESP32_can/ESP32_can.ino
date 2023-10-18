// Fill-in information from your Blynk Template here
#define BLYNK_TEMPLATE_ID           "TMPLwWBG3AuF"
#define BLYNK_DEVICE_NAME           "IVN Project"
//#define BLYNK_AUTH_TOKEN "GAxriIlhz9w-BaWhmDyCfTnOojmsPEoJ"
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

String Data,temperature,humidity,pressure,acceleration,breaking,oversteer,collision,rollover,temp,hum,pres,magnet;

void setup() 
{
  Wire.begin(9); 
  Serial.begin(115200);
  Wire.onReceive(receiveEvent); 
  BlynkEdgent.begin();
}

void loop() 
{
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
BlynkEdgent.run();
delay(1000);
}

void receiveEvent(int howMany) 
{
  Data="";
  while (Wire.available()) {  
  Data +=(char)Wire.read();       
}
}
