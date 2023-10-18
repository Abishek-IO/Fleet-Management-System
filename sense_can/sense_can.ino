#include <Arduino_LSM9DS1.h>
#include <Arduino_LPS22HB.h>
#include <Arduino_HTS221.h>
#include <Wire.h>

String temp,hum,pres,combine,padding="0",accelerationdata,breakingdata,oversteerdata,collisiondata,rolloverdata,tempwarning,humwarning,preswarning,magnetwarning;
int oversteer=0,breaking=0,acceleration=0,rollover=0,collision=0,tempdata=0,humdata=0,presdata=0,magnet=0;

void setup() {
  
  Serial.begin(9600);
  Wire.begin(9);
  Wire.onRequest(requestEvent);
  
  if (!IMU.begin()) {
    Serial.println("Failed to initialize IMU!");
    while (1);
  }
  if (!HTS.begin()) {
    Serial.println("Failed to initialize humidity temperature sensor!");
    while (1);
  }
  if (!BARO.begin()) {
    Serial.println("Failed to initialize pressure sensor!");
    while (1);
  }
}

void loop() {

float x, y, z, x1, y1, z1, x2, y2, z2;
float temperature = HTS.readTemperature();
float humidity    = HTS.readHumidity();
float pressure = BARO.readPressure();

  if (IMU.accelerationAvailable()) {
    IMU.readAcceleration(x, y, z);
    Serial.println("Accelerometer Data");
    Serial.print("X = ");
    Serial.print(x);
    Serial.print('\n');
    Serial.print("Y = ");
    Serial.print(y);
    Serial.print('\n');
    Serial.print("Z = ");
    Serial.println(z);
    Serial.println();
  }
  if (IMU.gyroscopeAvailable()) {
    IMU.readGyroscope(x1, y1, z1);
    Serial.println("Gyroscope Data");
    Serial.print("X = ");
    Serial.print(x1);
    Serial.print('\n');
    Serial.print("Y = ");
    Serial.print(y1);
    Serial.print('\n');
    Serial.print("Z = ");
    Serial.println(z1);
    Serial.println();
  }
  if (IMU.magneticFieldAvailable()) {
    IMU.readMagneticField(x2, y2, z2);
    Serial.println("Magnetometer Data");
    Serial.print("X = ");
    Serial.print(x2);
    Serial.print('\n');
    Serial.print("Y = ");
    Serial.print(y2);
    Serial.print('\n');
    Serial.print("Z = ");
    Serial.println(z2);
    Serial.println();
  }
  Serial.print("Temperature = ");
  temperature = temperature-4.00;
  Serial.print(temperature);
  Serial.println(" °C");

  Serial.print("Humidity    = ");
  humidity = humidity-50.00;
  Serial.print(humidity);
  Serial.println(" %");

  Serial.print("Pressure = ");
  Serial.print(pressure);
  Serial.println(" kPa");

  if(x>1.00)//for sudden acceleration
  {
  acceleration++;
  }
  else if(x<-1.00)//for harsh breaking
  {
    breaking++;
  }
  else if(x>2.00||y>2.00)//for collision
  {
    collision=1;
  }
  else if(y>1.00||y<-1.00)//oversteer
  {
   oversteer++; 
  }
  else if(x1>200.00||y1>200.00||z1>200.00||x1<-200.00||y1<-200.00||z1<-200.00)//rollover
  {
    rollover=1;
  }
  else if(temperature>35.00)
  {
    tempdata=1;
  }
  else if(humidity>90.00)
  {
    humdata=1;
  }
  else if(pressure>150.00)
  {
    presdata=1;
  }
  else if(x2>300.00||y2>300.00||z2>300.00||x2<-300.00||y2<-300.00||z2<-300.00)
  {
    magnet=1;
  }
  else
  {
    Serial.println("Do nothing");
  }
 
  if(acceleration<10)
  {
    accelerationdata = padding+String(acceleration);
  }
  else
  {
    accelerationdata = String(acceleration);
  }

  if(breaking<10)
  {
    breakingdata = padding+String(breaking);
  }
  else
  {
    breakingdata = String(breaking);
  }

  if(oversteer<10)
  {
    oversteerdata = padding+String(oversteer);
  }
  else
  {
    oversteerdata = String(oversteer);
  }
  
  if(pressure<100.00)
  {
    pres = padding+String(pressure);
  }
  else
  {
    pres = String(pressure);
  }

  temp = String(temperature);
  hum = String(humidity);
  collisiondata = String(collision);
  rolloverdata = String(rollover);
  tempwarning = String(tempdata);
  humwarning = String(humdata);
  preswarning = String(presdata);
  magnetwarning = String(magnet);
  combine = temp+hum+pres+accelerationdata+breakingdata+oversteerdata+collisiondata+rolloverdata+tempwarning+humwarning+preswarning+magnetwarning; 
  delay(1000);
}

void requestEvent()
{
  Wire.write(combine.c_str());         
}
