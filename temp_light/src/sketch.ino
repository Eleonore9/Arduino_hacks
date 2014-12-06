char light_char[10];
char temp_char[10];

//Global variables ligth sensor
int sensorlight = 2;

//Global variables temperature sensor
int sensortemp = 0;

void setup()
{
    Serial.begin(9600); //Starts the Serial connection
    pinMode(13, OUTPUT); //Using the LED at the pin 13
}

void loop()
{
    Light:
    int LDRValue = analogRead(sensorlight);
    float lightInt = (float) (1023 - LDRValue) * 10 / LDRValue;
    //delay(1000); //Sets the speed by which LDR send a value to Arduino

    Temp:
    int reading = analogRead(sensortemp);
    // converting that reading to voltage, for 3.3v arduino use 3.3
    float voltage = reading * 5.0;
    voltage /= 1024.0; 
    float temperatureC = (voltage - 0.5) * 100 ; //converting from 10 mv per degree wit 500 mV offset
                                                 //to degrees ((volatge - 500mV) times 100)
    //delay(1000);    

    // Printing stuffs:
    //Serial.print("Light: ");
    //Serial.print(lightInt);
    //Serial.print(", Temp: ");
    //Serial.println(temperatureC);

    dtostrf(lightInt, 2, 2, light_char);
    dtostrf(temperatureC, 2, 2, temp_char);    

    String csvline = String(light_char) + "," + String(temp_char);
    Serial.println(csvline);

    delay(800);
}
