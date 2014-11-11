/*
Code for a simple web server
using the code sample on Arduino
website: http://arduino.cc/en/Tutorial/WiFiWebServer

Project using my Arduino Uno, wifi Shield and light sensor
*/

#include <SPI.h>
#include <WiFi.h>

// Global variables
// for the server
char ssid[] = "";
char pass[] = "";
int status = WL_IDLE_STATUS;
WiFiServer server(80);

// for the sensor
int light_sensitivity = 20; //Thresold value
int light_sensitivity2 = 10; //Thresold value
float Rsensor; //Resistance of sensor

void setup()
{
    //Initialize serial and wait for port to open:
    Serial.begin(9600);
    while (!Serial);

    // check for the presence of the shield:
    if (WiFi.status() == WL_NO_SHIELD) {
        Serial.println("WiFi shield not present");
        // don't continue:
        while(true);
    }
  
    // try to connect to WiFi network:
    while ( status != WL_CONNECTED) {
        Serial.print("Attempting to connect to SSID: ");
        Serial.println(ssid);
        // connect to WPA/WPA2 network:    
        status = WiFi.begin(ssid, pass);
        // wait 10 seconds for connection:
        delay(10000);
    }
    server.begin();
    // you're connected now, so print out the status:
    printWifiStatus();
}


void loop()
{
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("new client");
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 3");  // refresh the page automatically every 5 sec
          client.println();
          client.println("<!DOCTYPE HTML>");
          client.println("<html>");

        // code to get the sensor data from analog pin A0:
            int sensorReading = analogRead(0);
            
            // LIGHT SENSOR
            //Rsensor = (float) (1023 - sensorReading) * 10 / sensorReading;
            // TEMPERATURE SENSOR
            
            // converting that reading to voltage, for 3.3v arduino use 3.3
            float voltage = sensorReading * 5.0;
            voltage /= 1024.0; 
            float temperatureC = (voltage - 0.5) * 100;

            delay(100);
            client.print("analog input ");
            client.print(" is ");
            //client.print(Rsensor);
            client.print(temperatureC);
            client.print(" degrees C");
            client.println("<br />");      

        client.println("</html>");
           break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);
   
    // close the connection:
    client.stop();
    Serial.println("client disonnected");
  }
}

void printWifiStatus() {
  // print the SSID of the network you're attached to:
  Serial.print("SSID: ");
  Serial.println(WiFi.SSID());

  // print your WiFi shield's IP address:
  IPAddress ip = WiFi.localIP();
  Serial.print("IP Address: ");
  Serial.println(ip);

  // print the received signal strength:
  long rssi = WiFi.RSSI();
  Serial.print("signal strength (RSSI):");
  Serial.print(rssi);
  Serial.println(" dBm");
}
