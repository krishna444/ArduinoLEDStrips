#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
#define LIGHT_THRESHOLD 50

class RotatingColor
{
private:
    static const int MIN_DELAY = 120;
    static const int MAX_DELAY = 480;
    static const bool MULTI_DIRECTION=false;
    int delay_millis;
    int colorIndex;
    uint16_t min_delay;
    uint16_t max_delay;
    bool multi_direction;
    bool forwardDirection=true;
    int selectedPixel;
    Adafruit_NeoPixel strip;
    TKLightSensor *lightSensor;
    TKThermistor *thermistor;

public:
    RotatingColor();
    RotatingColor(uint16_t _delay);
    RotatingColor(uint16_t _min_delay, uint16_t _max_delay);
    void process(bool _multi_direction, bool _temperature);
    void singleDirection(bool temp);
    void multiDirection();

};