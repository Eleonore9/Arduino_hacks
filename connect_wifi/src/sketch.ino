#include <WiFi.h>

// Trying to connect to a network


//Global variables
char ssid[] = "ODINET";
char pass[] = "****";
int status = WL_IDLE_STATUS;

void setup()
{
    Serial.begin(9600);
    // Try to connect 
    Serial.println("Attempting to connect...");
    status = WiFi.begin(ssid, pass);
    // If you're not connected
    if (status != WL_CONNECTED) {
        Serial.println("F#*@! Couldn't connect :[");
        while(true);
    }
    // If you're connected
        Serial.println("Yay! You're connected 8-)");
}

void loop()
{
}
