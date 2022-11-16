#include "RotatingColor.h"
#include<stdio.h>

int colors[][3] = {
    {148, 0, 211}, // Voilet
    {75, 0, 130},  // Indigo
    {0, 0, 255},   // Blue
    {0, 255, 0},   // Green
    {255, 255, 0}, // Yellow
    {255, 127, 0}, // Orange
    {255, 0, 0}    // Red
};
const int NCOLOURS = sizeof(colors) / sizeof(*colors);
int colorIndex = 0;
int max_delay = 420, min_delay = 120;
int delay_mills = random(min_delay, max_delay);



RotatingColor::RotatingColor():RotatingColor(min_delay,max_delay)
{}
RotatingColor::RotatingColor(uint16_t _delay):RotatingColor(_delay,_delay)
{}
RotatingColor::RotatingColor(uint16_t _min_delay,uint16_t _max_delay)
{
    min_delay=_min_delay;
    max_delay=_max_delay;
    Serial.begin(115200);
    strip.begin();      
}


void RotatingColor::process()
{    
    float light = lightSensor.read();
    Serial.print(light);
    if (light > LIGHT_THRESHOLD)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    } 
    strip.clear();
    strip.setPixelColor(selectedPixel, colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    strip.setPixelColor((selectedPixel+NUMPIXELS/2)%NUMPIXELS, colors[(colorIndex+1)%NCOLOURS][0], colors[(colorIndex+1)%NCOLOURS][1], colors[(colorIndex+1)%NCOLOURS][2]);
    selectedPixel++;
    if (selectedPixel >= NUMPIXELS)
    {
        selectedPixel = 0;
        colorIndex++;
        if (colorIndex >= NCOLOURS)
        {
            colorIndex = 0;
        }
        delay_mills = random(min_delay, max_delay);
    }

    strip.show();
    delay(delay_mills);
}