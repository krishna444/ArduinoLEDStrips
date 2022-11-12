#include <Adafruit_NeoPixel.h>
#include "TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
#define LIGHT_THRESHOLD 40

int colors[7][3] = {{148, 0, 211}, {75, 0, 130}, {0, 0, 255}, {0, 255, 0}, {255, 255, 0}, {255, 127, 0}, {255, 0, 0}};
;
int selectedPixel = 0;
int colorIndex = 0;
int max_delay = 480, min_delay = 100;
int delay_mills = random(min_delay, max_delay);

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
    if (light > LIGHT_THRESHOLD)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    }
    strip.clear();
    strip.setPixelColor(selectedPixel, colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    selectedPixel++;
    if (selectedPixel >= NUMPIXELS)
    {
        selectedPixel = 0;
        colorIndex++;
        if (colorIndex >= 7)
        {
            colorIndex = 0;
        }
        delay_mills = random(min_delay, max_delay);
    }

    strip.show();
    delay(delay_mills);
}
