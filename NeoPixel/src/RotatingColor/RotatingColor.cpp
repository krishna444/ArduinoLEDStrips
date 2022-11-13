#include "RotatingColor.h"

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
int selectedPixel = 0;
int colorIndex = 0;
int max_delay = 480, min_delay = 100;
int delay_mills = random(min_delay, max_delay);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

TKLightSensor lightSensor(I0);

RotatingColor::RotatingColor()
{
    Serial.begin(115200);
    strip.begin();      
}

void RotatingColor::process()
{    
    float light = lightSensor.read();
    if (light > LIGHT_THRESHOLD)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    } 
    strip.clear();
    strip.setPixelColor(selectedPixel, colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
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