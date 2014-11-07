#include <SPI.h>
#include <WiFi.h> // In this sample we use WIFI library.
#include <PubSubClient.h> // Include library that supports mqtt protocol.
#include <osio_client.h> // Include client library for OpenSensors.

// Global variables
char ssid[] = "CampusGuest"; // Name of my WIFI network.
char pass[] = "****"; // WIFI network password
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
int light_sensitivity = 20; //Thresold value
int light_sensitivity2 = 10; //Thresold value
float Rsensor; //Resistance of sensor
char rLightSensor[10];


void setup()
{
    //Initialize serial:
    Serial.begin(9600);
    Serial.println("Initializing...");
    while (!Serial);

    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while(true);
    }
  
    // try to connect to WiFi network:
    while ( status != WL_CONNECTED) {
        Serial.print("Attempting to connect to network ");
        Serial.println(ssid);
        // connect to WPA/WPA2 network:    
        //status = WiFi.begin(ssid, pass); //password needed
        status = WiFi.begin(ssid); // no password needed
        // wait 10 seconds for connection:
        delay(10000);
        Serial.print("Connected to ");
        Serial.println(ssid);
        //print MAC address:
        WiFi.macAddress(mac);
        Serial.print("MAC: ");
        Serial.print(mac[5],HEX);
        Serial.print(":");
        Serial.print(mac[4],HEX);
        Serial.print(":");
        Serial.print(mac[3],HEX);
        Serial.print(":");
        Serial.print(mac[2],HEX);
        Serial.print(":");
        Serial.print(mac[1],HEX);
        Serial.print(":");
        Serial.println(mac[0],HEX);
    }
}

void loop()
{
    char message[255];
    char time[50];
    memset(message, 0, 255);
    memset(time, 0, 50);    

    // code to get the sensor data from analog pin A0:
    int sensorReading = analogRead(0);
    Rsensor = (float) (1023 - sensorReading) * 10 / sensorReading;
    sprintf(rLightSensor, "%f", Rsensor); // converts float to a string (here a char*)
    strcpy(message, "Light intensity at ");
    itoa(millis() / 1000, time, 10);
    strcat(message, time);
    strcat(message, " - analog input: ");
    strcat(message, rLightSensor);

    if (osioClient.publish("/users/Ele/Light-intensity-ODI", message))
    {
    Serial.print("Message published - resistance: ");
    Serial.print(Rsensor);
    Serial.print(" - converted to: ");
    Serial.println(Rsensor);
    }
    else
    {
    Serial.println("Error publishing message.");
    }
    delay(5000);
}
