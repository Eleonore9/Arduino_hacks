//Sketch for a light dependent resistor (LDR) module

//Global variables
int LDRValue; //LDR value
int light_sensitivity = 40; //Thresold value
int light_sensitivity2 = 10; //Thresold value
float Rsensor; //Resistance of sensor

void setup()
{
    Serial.begin(9600); //Starts the Serial connection
    pinMode(13, OUTPUT); //Using the LED at the pin 13
}

void loop()
{
    LDRValue = analogRead(1);//Reads LDR values at A0
    //Serial.println(LDRValue);
    Rsensor = (float) (1023 - LDRValue) * 10 / LDRValue;
    //Serial.println(Rsensor, DEC); 
    delay(1500); //Sets the speed by which LDR send a value to Arduino
    if (Rsensor < light_sensitivity)
    {
        if (Rsensor < light_sensitivity2)
        {
            Serial.print(Rsensor);
            Serial.println(" - The light is super bright!");
        }
        else
        {
        digitalWrite(13, HIGH);
        Serial.print(Rsensor);
        Serial.println(" - The light is on");
        }
    }
    else
    {
        digitalWrite(13, LOW);
        Serial.print(Rsensor);
        Serial.println(" - The light is off");
    }
}
