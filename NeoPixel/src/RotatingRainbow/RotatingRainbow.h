#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
#define LIGHT_THRESHOLD 40

class RotatingRainbow
{
private:
    uint16_t max_delay;
    uint16_t min_delay;
    int selectedPixel = 0;
    Adafruit_NeoPixel strip;
    TKLightSensor *lightSensor;

public:
    RotatingRainbow();
    RotatingRainbow(uint16_t _delay);
    RotatingRainbow(uint16_t _min_delay, uint16_t _max_delay);
    void process();
};