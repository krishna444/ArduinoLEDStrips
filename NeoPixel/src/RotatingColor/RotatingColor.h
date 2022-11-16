#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
#define LIGHT_THRESHOLD 40

class RotatingColor
{
private:
    uint16_t min_delay;
    uint16_t max_delay;
    int selectedPixel = 0;
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    TKLightSensor lightSensor=TKLightSensor(I0);
public:
    RotatingColor();
    RotatingColor(uint16_t _delay);
    RotatingColor(uint16_t _min_delay, uint16_t _max_delay);
    void process();
};