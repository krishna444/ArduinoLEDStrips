#include "RotatingRainbow.h"

int rainbow[][3] = {
    {148, 0, 211}, // Voilet
    {75, 0, 130},  // Indigo
    {0, 0, 255},   // Blue
    {0, 255, 0},   // Green
    {255, 255, 0}, // Yello
    {255, 127, 0}, // Orange
    {255, 0, 0}};  // Red

  
const int NUMCOLORS = sizeof(rainbow) / sizeof(*rainbow);

Adafruit_NeoPixel strip1 = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
TKLightSensor lightSensor1(I0);

int selectedPixel1=0;
int delay_millis=0;

RotatingRainbow::RotatingRainbow(){
    min_delay=120;
    max_delay=420;
    delay_millis=random(min_delay,max_delay);
    Serial.begin(115200);
    strip1.begin();      
    //RotatingRainbow(120,420);
}

RotatingRainbow::RotatingRainbow(uint16_t _delay)
{
    min_delay=_delay;
    max_delay=_delay;
    delay_millis=random(_delay,_delay);
    Serial.begin(115200);
    strip1.begin();      
}

RotatingRainbow::RotatingRainbow(uint16_t _min_delay, uint16_t _max_delay)
{
    min_delay = _min_delay;
    max_delay = _max_delay;
    delay_millis=random(_min_delay, _max_delay);
    Serial.begin(115200);
    strip1.begin();      
}



void RotatingRainbow::process(){
    /*float light = lightSensor1.read();
    if (light > 10)
    {
        strip1.clear();
        strip1.show();
        delay(2000);
        return;
    }*/
    strip1.clear();
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
