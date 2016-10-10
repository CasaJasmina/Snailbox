#include <Adafruit_NeoPixel.h>           //neopixel
#ifdef __AVR__
#include <avr/power.h>
#endif

#define LEDPIN            2  //pin to drive pixels
#define NUMPIXELS         17  //try to guess? 



Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);


//**********************************************************
//************OFF LAMP************************************
//**********************************************************
uint32_t offLamp() {
  uint32_t c = strip.Color(0, 0, 0);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
}


//**********************************************************
//************RELAX MOOD************************************
//**********************************************************
uint32_t focus(int r) {
  if (r < 255)r += 20;
  r = constrain(r, 0, 255);
  uint32_t c = strip.Color(r, (r * 4) / 5, r / 5);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  return r;
}


//**********************************************************
//************FOUCS MOOD************************************
//**********************************************************
uint32_t sprint(int f) {
  if (f < 255)f += 20;
  f = constrain(f, 0, 255);
  uint32_t c = strip.Color(f, f, f);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
  }
  strip.show();
  return f;
}


//**********************************************************
//************DO A WHEEL************************************
//**********************************************************
// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}


//**********************************************************
//************RAINBOW***************************************
//**********************************************************
uint16_t rainbow(uint8_t wait, uint16_t j) {
  uint16_t i;
  if (j > 255) j = 0;
  for (i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, Wheel((i + j) & 255));
  }
  strip.show();
  delay(wait);
  return j + 1;
}


//**********************************************************
//************stripBegin************************************
//**********************************************************
void stripBegin() {
  strip.begin(); // This initializes the NeoPixel library.
  strip.show(); // Initialize all pixels to 'off'
  Wire.begin();
  delay(1);
}


