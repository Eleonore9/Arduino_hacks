#include <Adafruit_NeoPixel.h>

// Global variables

#define N_LEDS 29.3666666

#define PIN     4

Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);

#define ledPin  13
#define thresholdvalue 100

int soundValue = 0;

void setup() {
     pinMode(ledPin, OUTPUT);
     Serial.begin(9600);
     strip.begin();
     strip.show();
}
 
int pos = 0, dir = 1; // Position, direction of "eye"


void loop() {
  int j;

  soundValue = analogRead(A0);//use A0 to read the electrical signal
  Serial.println(soundValue, DEC);

  if(soundValue > thresholdvalue) {
  digitalWrite(ledPin,HIGH);
  
 
  // Draw 5 pixels centered on pos.  setPixelColor() will clip any
  // pixels off the ends of the strip, we don't need to watch for that.
  strip.setPixelColor(pos - 2, 0x100000); // Dark red
  strip.setPixelColor(pos - 1, 0x800000); // Medium red
  strip.setPixelColor(pos    , 0xFF3000); // Center pixel is brightest
  strip.setPixelColor(pos + 1, 0x800000); // Medium red
  strip.setPixelColor(pos + 2, 0x100000); // Dark red
  // Bounce off ends of strip
  pos += dir;
  if(pos < 0) {
    pos = 1;
    dir = -dir;
  } else if(pos >= strip.numPixels()) {
    pos = strip.numPixels() - 2;
    dir = -dir;
  }

  strip.show();

  delay(50);
  }

  digitalWrite(ledPin,LOW);
  // Rather than being sneaky and erasing just the tail pixel,
  // it's easier to erase it all and draw a new one next time.
  for(j=-2; j<= 2; j++) strip.setPixelColor(pos+j, 0);
  delay(50);

  // // Bounce off ends of strip
  // pos += dir;
  // if(pos < 0) {
  //   pos = 1;
  //   dir = -dir;
  // } else if(pos >= strip.numPixels()) {
  //   pos = strip.numPixels() - 2;
  //   dir = -dir;
  // }
}

