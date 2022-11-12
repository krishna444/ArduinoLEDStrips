#include <Adafruit_NeoPixel.h>
#include "TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
int shift = 0;
int max_delay = 420, min_delay = 50;
int delay_mills = random(min_delay, max_delay);
int selectedPixel = 0;
// int colorIndex=0;
int rainbow[7][3] = {{148, 0, 211}, {75, 0, 130}, {0, 0, 255}, {0, 255, 0}, {255, 255, 0}, {255, 127, 0}, {255, 0, 0}};
;

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
TKLightSensor lightSensor(I0);

void setup()
{
    Serial.begin(115200);
    strip.begin();
}

void loop()
{
    float light = lightSensor.read();
    if (light > 30)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    }
    for (int i = 0; i < NUMPIXELS; i++)
    {
        strip.setPixelColor(i, 0, 0, 0);
    }
    for (int index = 0; index < 7; index++)
    {
        // if(selectedPixel+index<NUMPIXELS)
        strip.setPixelColor((selectedPixel + index) % NUMPIXELS, rainbow[index][0], rainbow[index][1], rainbow[index][2]);
    }
    selectedPixel++;
    if (selectedPixel >= NUMPIXELS)
    {
        selectedPixel = 0;
        delay_mills = random(min_delay, max_delay);
    }
    strip.show();
    delay(delay_mills);
}