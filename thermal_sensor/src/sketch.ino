#include <Time.h> 

int sensorpin = 0; //Pin for the temperature sensor
 
void setup()
{
  Serial.begin(9600);  //Start the serial connection with the computer
                       //to view the result open the serial monitor 
}
 
void loop() // run over and over again
{
    //getting the voltage reading from the temperature sensor
    int reading = analogRead(sensorpin);  
     
    // converting that reading to voltage, for 3.3v arduino use 3.3
    float voltage = reading * 5.0;
    voltage /= 1024.0; 
     
    //print out the voltage
    //Serial.print(voltage); 
    //Serial.println(" volts");
     
    // now print out the temperature
    float temperatureC = (voltage - 0.5) * 100 ; //converting from 10 mv per degree wit 500 mV offset
                                                 //to degrees ((volatge - 500mV) times 100)
    //Serial.print(hour());
    //printDigits(minute());
    //printDigits(second());
    Serial.print(",");
    Serial.println(temperatureC); 
    //Serial.print(" degrees C * ");
     
    // now convert to Fahrenheight
    //float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    //Serial.print(temperatureF); 
    //Serial.println(" degrees F");
     
    delay(1000); //waiting a second
}
