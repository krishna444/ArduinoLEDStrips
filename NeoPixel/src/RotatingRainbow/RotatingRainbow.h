#include <Adafruit_NeoPixel.h>
#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
#include <Arduino.h>
#define PIN 7
#define NUMPIXELS 20

class RotatingRainbow
{
protected:
     uint16_t max_delay;
     uint16_t min_delay;   
public:
    RotatingRainbow();
    RotatingRainbow(uint16_t delay);
    RotatingRainbow(uint16_t min_delay,uint16_t max_delay);
    void run();    
};