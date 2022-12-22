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

RotatingRainbow::RotatingRainbow() : RotatingRainbow(MIN_DELAY, MAX_DELAY)
{
}

RotatingRainbow::RotatingRainbow(uint16_t _delay) : RotatingRainbow(_delay, _delay)
{
}

RotatingRainbow::RotatingRainbow(uint16_t _min_delay, uint16_t _max_delay)
{
    this->strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    this->lightSensor = new TKLightSensor(I0);
    min_delay = _min_delay;
    max_delay = _max_delay;
    delay_millis = random(_min_delay, _max_delay);
    strip.begin();
}

void RotatingRainbow::process()
{
    float light = this->lightSensor->read();
    if (light > LIGHT_THRESHOLD)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    }
    strip.clear();
    for (int index = 0; index < NUMCOLORS; index++)
    {
        strip.setPixelColor((selectedPixel + index) % NUMPIXELS, rainbow[index][0], rainbow[index][1], rainbow[index][2]);
    }
    selectedPixel++;
    if (selectedPixel >= NUMPIXELS)
    {
        selectedPixel = 0;
        delay_millis = random(min_delay, max_delay);
    }
    strip.show();
    delay(delay_millis);
}
