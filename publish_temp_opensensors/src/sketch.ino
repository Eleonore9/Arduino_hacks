#include <SPI.h>
#include <WiFi.h> // In this sample we use WIFI library.
#include <PubSubClient.h> // Include library that supports mqtt protocol.
#include <osio_client.h> // Include client library for OpenSensors.

// Global variables
char ssid[] = ""; // Name of my WIFI network.
char pass[] = ""; // WIFI network password
byte mac[6]; // the MAC address of my Wifi shield.
int status = WL_IDLE_STATUS;
WiFiClient wifiClient; // Wireless client.
// Instance of client library class.
// Client (wired or wireless), user name, device ID, device password should be supplied.
// There are two optional parameters: callback (we need it is planning to read messages from topic),
// server name (opensensors.io by default).
// In this sample don't need to supply callback and use default server name.
OSIOClient osioClient(wifiClient, "Ele", "141", "g4d7PDWs");

// for the sensor
int sensorpin = 0;

void setup()
{
    //Initialize serial:
    Serial.begin(9600);
    //Serial.println("Initializing...");
    while (!Serial);

    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while(true);
    }
  
    // try to connect to WiFi network:
    while ( status != WL_CONNECTED) {
        //Serial.print("Attempting to connect to network ");
        //Serial.println(ssid);
        // connect to WPA/WPA2 network:    
        status = WiFi.begin(ssid, pass); //password needed
        // wait 10 seconds for connection:
        delay(10000);
        //Serial.print("Connected to ");
        //Serial.println(ssid);
    }
}

void loop()
{
    char message[255];
    char time[50];
    memset(message, 0, 255);
    memset(time, 0, 50);    

    char tempC [33];
    char tempF [33];

    //getting the voltage reading from the temperature sensor
    int reading = analogRead(sensorpin);  
     
    // converting that reading to voltage, for 3.3v arduino use 3.3
    float voltage = reading * 5.0;
    voltage /= 1024.0; 
     
    // print out the voltage
    Serial.print(voltage); 
    Serial.println(" volts");
    
    // now print out the temperature
    float temperatureC = (voltage - 0.5) * 100 ;  //converting from 10 mv per degree wit 500 mV offset
                                                   //to degrees ((volatge - 500mV) times 100)
    Serial.println(temperatureC); 
    //Serial.print(" degrees C - ");
     
    // now convert to Fahrenheight
    float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
    //Serial.print(temperatureF); //Serial.println(" degrees F");
    
    //Convert temperature:
    sprintf(tempC, "%f", temperatureC); // converts float to a string
    sprintf(tempF, "%f", temperatureF); // converts float to a string
    
    //Building the message:
    strcpy(message, "Light intensity at ");
    itoa(millis() / 1000, time, 10);
    strcat(message, time);
    strcat(message, " - Temp: ");
    strcat(message, tempC);
    strcat(message, " degrees C = ");
    strcat(message, tempF);
    strcat(message, " degrees F");

    if (osioClient.publish("/users/Ele/Temp-ODI", message))
    {
    Serial.println("Message published!");
    }
    //else
    //{
    //Serial.println("Error publishing message.");
    //}
    delay(500);
}
