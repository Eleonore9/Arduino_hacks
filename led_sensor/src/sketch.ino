// Trying the LED light sensor from Arduino
// webiste: http://playground.arduino.cc/Learning/LEDSensor

#include <SPI.h>

#define LED_N_SIDE 2
#define LED_P_SIDE 3

void setup()
{
  Serial.println("Hi!");
  Serial.begin(9600);
  while (!Serial);
}

void loop()
{
  unsigned int j;
  
  Serial.println("Hi there!");

  // Apply reverse voltage, charge up the pin and led capacitance
  pinMode(LED_N_SIDE,OUTPUT);
  pinMode(LED_P_SIDE,OUTPUT);
  digitalWrite(LED_N_SIDE,HIGH);
  digitalWrite(LED_P_SIDE,LOW);
  
  Serial.println(digitalRead(LED_N_SIDE));
  Serial.println(digitalRead(LED_P_SIDE));

  // Isolate the pin 2 end of the diode
  pinMode(LED_N_SIDE,INPUT);
  digitalWrite(LED_N_SIDE,LOW);  // turn off internal pull-up resistor

  // Count how long it takes the diode to bleed back down to a logic zero
  for ( j = 0; j < 30000; j++) {
    if ( digitalRead(LED_N_SIDE)==0) break;
  }
  // You could use 'j' for something useful, but here we are just using the
  // delay of the counting.  In the dark it counts higher and takes longer, 
  // increasing the portion of the loop where the LED is off compared to 
  // the 1000 microseconds where we turn it on.

  // Turn the light on for 1000 microseconds
  digitalWrite(LED_P_SIDE,HIGH);
  digitalWrite(LED_N_SIDE,LOW);
  pinMode(LED_P_SIDE,OUTPUT);
  pinMode(LED_N_SIDE,OUTPUT);
  delayMicroseconds(1000);
  // we could turn it off, but we know that is about to happen at the loop() start
}
