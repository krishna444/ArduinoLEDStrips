#include "RotatingRainbow.h"

int rainbow[7][3] = {
    {148, 0, 211}, // Voilet
    {75, 0, 130},  // Indigo
    {0, 0, 255},   // Blue
    {0, 255, 0},   // Green
    {255, 255, 0}, // Yello
    {255, 127, 0}, // Orange
    {255, 0, 0}};  // Red

  
int NUMCOLORS = sizeof(rainbow) / sizeof(*rainbow);

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
TKLightSensor lightSensor1(I0);

int selectedPixel1=0;
int delay_millis=0;

RotatingRainbow::RotatingRainbow(){
    min_delay=_120;
    max_delay=420;
    delay_millis=random(min_delay,max_delay);
}

RotatingRainbow::RotatingRainbow(uint16_t _delay)
{
    min_delay=_delay;
    max_delay=_delay;
    delay_millis=random(_delay,_delay);
}

RotatingRainbow::RotatingRainbow(uint16_t _min_dealy, uint16_t _max_dealy)
{
    min_delay = _min_dealy;
    max_delay = _max_delay;
    delay_millis=random(_min_delay, _max_delay);
}

void RotatingRainbow::run(){
    float light = lightSensor1.read();
    if (light > 30)
    {
        strip1.clear();
        strip1.show();
        delay(2000);
        return;
    }
    for (int index = 0; index < NUMCOLORS; index++)
    {        
        strip1.setPixelColor((selectedPixel1 + index) % NUMPIXELS, rainbow[index][0], rainbow[index][1], rainbow[index][2]);
    }
    selectedPixel1++;
    if (selectedPixel1 >= NUMPIXELS)
    {
        selectedPixel1 = 0;
        delay_millis = random(min_delay, max_delay);
    }
    strip1.show();
    delay(delay_millis);
}
