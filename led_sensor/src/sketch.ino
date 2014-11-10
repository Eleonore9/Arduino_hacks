// Trying the LED light sensor from Arduino

int LIGHT_SENSOR = 0;
int LED = 13;

int THRESHOLD = 200;

void setup() {
    pinMode(LIGHT_SENSOR, INPUT);
    pinMode(LED, OUTPUT);
    Serial.begin(9600);
}
void loop() {
    Serial.println("*************");
    int x = analogRead(LIGHT_SENSOR);
    Serial.println(x);
    
    if(x < THRESHOLD) {
        digitalWrite(LED, HIGH);
    }    
    else {
        digitalWrite(LED, LOW);
    }

    delay(1000);
}
