double a = 12.65789;
char b[9];
void setup() {
  Serial.begin(9600);

}

void loop() {
  Serial.println(a,5);
  dtostrf(a,7,5,b);
  Serial.println(b);
  Serial.println(b[7]);
  delay(2000);
}
