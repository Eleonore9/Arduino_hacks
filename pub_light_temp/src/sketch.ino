#include <SPI.h>
#include <WiFi.h> // In this sample we use WIFI library.
#include <PubSubClient.h> // Include library that supports mqtt protocol.
#include <osio_client.h> // Include client library for OpenSensors.
// Global variables
char ssid[] = "devolo-resin"; // Name of my WIFI network.
char pass[] = "resin.io"; // WIFI network password
byte mac[6]; // the MAC address of my Wifi shield.
int status = WL_IDLE_STATUS;
WiFiClient wifiClient; // Wireless client.
// Instance of client library class.
// Client (wired or wireless), user name, device ID, device password should be supplied.
// There are two optional parameters: callback (we need it is planning to read messages from topic),
// server name (opensensors.io by default).
// In this sample don't need to supply callback and use default server name.
OSIOClient osioClient(wifiClient, "Ele", "141", "g4d7PDWs");


char light_char[10];
char temp_char[10];

//Global variables ligth sensor
int sensorlight = 2;

//Global variables temperature sensor
int sensortemp = 0;


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
status = WiFi.begin(ssid, pass); //password needed
//status = WiFi.begin(ssid); // no password needed
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

    strcpy(message, "Light + temp at Ldn FabLab: ");
    itoa(millis() / 1000, time, 10);
    strcat(message, time);
    strcat(message, light_char);
    strcat(message, ", ");
    strcat(message, temp_char);

    if (osioClient.publish("/users/Ele/Fablab_test", message))
    {
    Serial.println("message published!");
    }
    else
    {
    Serial.println("Error publishing message.");
    }

    delay(800);
}
