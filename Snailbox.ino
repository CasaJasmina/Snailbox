/****************************************************************************
  SNAILBOX

  giacomoleonzi@gmail.com

  this sketch is for a proejct called SNAILBOX, snailbox.cj@gmail.com

  major features:

  - connect to WPA SSID

  - manage colors, intensity and animation of neopixel(ws2812b)

  - read data coming from an 3x accelerometer (MMA7660) the grove one


******************************************************************************/
#include "axis.h"
#include "strip.h"
#include "wifi.h"


WiFiClient client;

int delayval = 500; // delay for half a second
int ldrPin = A1;
int threshold = 100; //threshold of LDR lecture
bool rlx = false;
bool fcs = false;
bool sprt = false;
/*

                    SETUP

*/

void setup()
{
  // IF YOU ARE USING AN AVR_ATtiny85 YOU NEED THIS
#if defined (__AVR_ATtiny85__)
  if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
#endif


  Serial.begin(9600);

  //**********************************************************
  //*************init  led strip******************************
  //**********************************************************
  stripBegin();

  //**********************************************************
  //*************starting accellerometer setup****************
  //**********************************************************
  accelBegin();

  //**********************************************************
  //************STARTING CONNECTION***************************
  //**********************************************************
  startConnection();

}

/*

                     LOOP


*/

int f = 0;
int delta = 10;
int r = 0;
uint16_t s = 0;

void loop()
{
  int mood = getPos();
  int ldr = analogRead(ldrPin);
  Serial.println(ldr);
  if (ldr <= threshold) {
    switch (mood) {


      //**********************
      //relax mood, warm light
      case 0:
        {
          Serial.println("Relax");
          if (!rlx) {
            send_event("Relax");
            rlx = true;
          }
          f = 0;
          r = rainbow(20, r);
          fcs = false;
          sprt = false;
          break;
        }


      //**********************
      //focus mood, strong light
      case 1:
        {
          Serial.println("Focus");
          if (!fcs) {
            send_event("Focus");
            fcs = true;
          }
          r = 0;
          f = focus(f);
          rlx = false;
          sprt = false;
          break;
        }


      //**********************
      //Sprint  mood, rainbow light
      case 2:
        {
          Serial.println("Sprint");
          if (!sprt) {
            send_event("Sprint");
            sprt = true;
          }
          s = sprint(s);
          rlx = false;
          fcs = false;
          break;
        }
    }
  }
  delay(200);
}
