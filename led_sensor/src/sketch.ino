// Trying the LED light sensor from Arduino

#include <SPI.h>
#include <WiFi.h> // In this sample we use WIFI library.
#include <PubSubClient.h> // Include library that supports mqtt protocol.
#include <osio_client.h> // Include client library for OpenSensors.


// Global variables
char ssid[] = "ODINET"; // Name of my WIFI network.
char pass[] = "OpenData"; // WIFI network password
int status = WL_IDLE_STATUS;
WiFiClient wifiClient; // Wireless client.
// Instance of client library class.
// Client (wired or wireless), user name, device ID, device password should be supplied.
// There are two optional parameters: callback (we need it is planning to read messages from topic),
// server name (opensensors.io by default).
// In this sample don't need to supply callback and use default server name.
OSIOClient osioClient(wifiClient, "Ele", "141", "g4d7PDWs");

// for the sensor
int LED = 13;
int LIGHT_SENSOR = 2;
int THRESHOLD = 200;

void setup() {
    pinMode(LIGHT_SENSOR, INPUT);
    pinMode(LED, OUTPUT);

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
        status = WiFi.begin(ssid, pass); //password needed
        //status = WiFi.begin(ssid); // no password needed
        // wait 10 seconds for connection:
        delay(10000);
        Serial.print("Connected to ");
        Serial.println(ssid);
    }
}
void loop() {
    char message[255];
    char time[50];
    char buffer [33];
    memset(message, 0, 255);
    memset(time, 0, 50);    

    // code to get the sensor data from analog pin A0:
    int x = analogRead(LIGHT_SENSOR);
    Serial.println(x);

    itoa(x, buffer, 10);    

    strcpy(message, "Light intensity: ");
    strcat(message, buffer);

    if (osioClient.publish("/users/Ele/Light-intensity-ODI", message))
    {
    Serial.println("Message published.");
    }
    else
    {
    Serial.println("Error publishing message.");
    }

    delay(1000);
}
