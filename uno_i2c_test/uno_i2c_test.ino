#include <Wire.h>
String combine;
void setup() {
  
  Serial.begin(9600);
  Wire.begin();
}

void loop() {
combine = "hello";  
Wire.beginTransmission(9); 
  Wire.write(combine.c_str());         
  Wire.endTransmission();
  
  delay(1000);
}
