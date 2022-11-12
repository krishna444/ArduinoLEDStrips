#define PROD
#include <Adafruit_NeoPixel.h>
#ifdef PROD
#include "TinkerKit.h"
#endif
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
int shift = 0;
int max_delay = 420, min_delay = 50;
int delay_mills = random(min_delay, max_delay);
int selectedPixel = 0;
// int colorIndex=0;
int rainbow[7][3] = {
    {148, 0, 211}, // Voilet
    {75, 0, 130},  // Indigo
    {0, 0, 255},   // Blue
    {0, 255, 0},   // Green
    {255, 255, 0}, // Yello
    {255, 127, 0}, // Orange
    {255, 0, 0}};  // Red

int NUMCOLORS = sizeof(rainbow) / sizeof(*rainbow);

Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
#ifdef PROD
TKLightSensor lightSensor(I0);
#endif

void setup()
{
    Serial.begin(115200);
    strip.begin();
}

void loop()
{
    #ifdef PROD
    float light = lightSensor.read();
    if (light > 30)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    }
    #endif
    strip.clear();    
    for (int index = 0; index < NUMCOLORS; index++)
    {        
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