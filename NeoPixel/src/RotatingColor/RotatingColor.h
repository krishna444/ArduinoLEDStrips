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
    static const int MIN_DELAY=120;
    static const int MAX_DELAY=480;
    int delay_millis;
    int colorIndex;
    uint16_t min_delay;
    uint16_t max_delay;
    int selectedPixel;
    Adafruit_NeoPixel strip;
    TKLightSensor *lightSensor;

public:
    RotatingColor();
    RotatingColor(uint16_t _delay);
    RotatingColor(uint16_t _min_delay, uint16_t _max_delay);
    void process();
};