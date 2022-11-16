#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20

class RotatingRainbow
{
protected:
     uint16_t max_delay;
     uint16_t min_delay;   
public:
    RotatingRainbow();
    RotatingRainbow(uint16_t _delay);
    RotatingRainbow(uint16_t _min_delay,uint16_t _max_delay);
    void process();    
};