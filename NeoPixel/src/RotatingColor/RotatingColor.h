#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
#define LIGHT_THRESHOLD 40

class RotatingColor
{
public:
    RotatingColor();
    void process();
};