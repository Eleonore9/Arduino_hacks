// the setup routine runs once when you press reset:
void setup() {
  // initialize serial communication at 9600 bits per second:
  Serial.begin(9600);
}

// the loop routine runs over and over again forever:
void loop() {
 
  int lightSensorValue = analogRead(A1);
  //Serial.println(lightSensorValue);
 
  int co2SensorValue = analogRead(A0);
  //Serial.println(co2SensorValue);
 
  String csvLine = String(lightSensorValue) + ',' + String(co2SensorValue);
 
  Serial.println(csvLine);
 
  // every 800 milliseconds
  delay(800);
}