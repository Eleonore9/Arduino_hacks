#include <Adafruit_NeoPixel.h>

//Global variables
#define N_LEDS 29 //Numbers of leds on the strip
#define PIN 4 //led strip on digital pin 4


Adafruit_NeoPixel strip = Adafruit_NeoPixel(N_LEDS, PIN, NEO_GRB + NEO_KHZ800);


// #define low_red strip.Color(3, 0, 0)
// #define low_green strip.Color(0, 3, 0)
// #define med_red strip.Color(20, 0, 0)
// #define med_green strip.Color(0, 20, 0)
// #define hi_red strip.Color(40, 0, 0)
// #define hi_green strip.Color(0, 40, 0)


void setup() {
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
}