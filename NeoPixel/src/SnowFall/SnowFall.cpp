#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
#define PIN 7
#define NUMPIXELS 20

struct PixelState
{
    // is the pixel currently on
    boolean on;
    // time at which the pixel was turned on or off
    unsigned long timeMarkMs;
    // amount of time for which the pixel should remain off
    unsigned long offTimeMs;
    // selected colout if the pixel is on
    int selectedColour;
    // most recent max brightness. We keep this to stop us
    // sending colour changes to the pixels if it is unnecessary
    // this is important, because neopixels use a timing-based protocol
    int mostRecentBrightness;
    boolean increasing;
};

class SnowFall
{
private:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    // TKLightSensor lightSensor(I0);
    struct PixelState pixel[NUMPIXELS];
    uint16_t min_off_time_ms;
    uint16_t max_off_time_ms;
    uint16_t fade_time_ms;

public:
    static const int MIN_OFF_TIME_MS = 3000;
    static const int MAX_OFF_TIME_MS = 6000;
    static const int FADE_TIME_MS = 6000;
    const int COLOURS[10][3] = {
        {255, 128, 64},  // Red
        {64, 255, 64},   // Green
        {64, 64, 255},   // Blue
        {255, 255, 32},  // Yellow
        {255, 64, 255},  // Pink
        {64, 255, 255},  // Cyan
        {255, 255, 255}, // White
        {148, 64, 211},  // Voilet
        {75, 64, 130},   // Indigo
        {255, 127, 64}   // Orange
    };
    static const int NCOLOURS = sizeof(COLOURS) / sizeof(*COLOURS);
    SnowFall():SnowFall(MIN_OFF_TIME_MS,MAX_OFF_TIME_MS,FADE_TIME_MS)
    {
       /* this->min_off_time_ms = MIN_OFF_TIME_MS;
        this->max_off_time_ms = MAX_OFF_TIME_MS;
        this->fade_time_ms = FADE_TIME_MS;*/
    }
    SnowFall(uint16_t off_time, uint16_t fade_time):SnowFall(off_time,off_time,fade_time)
    {
    }
    SnowFall(uint16_t min_off_time, uint16_t max_off_time, uint16_t fade_time)
    {
        this->min_off_time_ms = min_off_time;
        this->max_off_time_ms = max_off_time;
        this->fade_time_ms = fade_time;
        this->init();
    }

    void init()
    {
        Serial.begin(115200);
        for (int i = 0; i < NUMPIXELS; i++)
        {
            pixel[i].on = false;
            pixel[i].timeMarkMs = millis();
            pixel[i].offTimeMs = random(MIN_OFF_TIME_MS, MAX_OFF_TIME_MS);
            pixel[i].increasing = true;
            pixel[i].selectedColour = random(NCOLOURS);
        }

        strip.begin(); // Allocate NeoPixel buffer
        strip.clear(); // Make sure strip is clear
        strip.show();
    }

    void process()
    {
        // float light = lightSensor.read();
        /*if (light > 50)
        {
            strip.clear();
            strip.show();
            delay(2000);
            return;
        }*/
        for (int i = 0; i < NUMPIXELS; i++)
        {
            // MAX_OFF_TIME_MS = 600;//map(dimmerValue, 0, 1024, 10000, 600);
            if (pixel[i].on)
            {
                // pixel is on
                if (millis() - pixel[i].timeMarkMs >= this->fade_time_ms)
                {
                    // time to turn the pixel off
                    strip.setPixelColor(i, 0, 0, 0);
                    pixel[i].timeMarkMs = millis();
                    pixel[i].offTimeMs = random(MIN_OFF_TIME_MS, MAX_OFF_TIME_MS);
                    Serial.print("off time");
                    Serial.print(pixel[i].offTimeMs);
                    Serial.println();
                    pixel[i].mostRecentBrightness = 0;
                    pixel[i].on = false;
                }
                else
                {
                    // calculate the new brightness as flaoting point
                    // this is the bit that you change if you want the fade pattern to change
                    float brightness = 1 - (millis() - pixel[i].timeMarkMs) / ((float)this->fade_time_ms);
                    brightness = brightness * brightness; // gamma correction

                    // ok. do we actually need to change the pixel colour?
                    int mostRecentBrightness = 200 * brightness;
                    if (mostRecentBrightness != pixel[i].mostRecentBrightness)
                    {
                        // yes we do
                        pixel[i].mostRecentBrightness = mostRecentBrightness;
                        strip.setPixelColor(i,
                                            (int)(COLOURS[pixel[i].selectedColour][0] * brightness),
                                            (int)(COLOURS[pixel[i].selectedColour][1] * brightness),
                                            (int)(COLOURS[pixel[i].selectedColour][2] * brightness));
                    }
                }
            }
            else
            {
                // pixel is off. do we need to turn it on?

                if (millis() - pixel[i].timeMarkMs > pixel[i].offTimeMs)
                {
                    pixel[i].on = true;
                    pixel[i].mostRecentBrightness = 0; // this will force an update next loop
                    pixel[i].selectedColour = random(NCOLOURS);
                    pixel[i].timeMarkMs = millis();
                    strip.setPixelColor(i,
                                        COLOURS[pixel[i].selectedColour][0],
                                        COLOURS[pixel[i].selectedColour][1],
                                        COLOURS[pixel[i].selectedColour][2]);
                }
            }
        }
        strip.show();
    }
};
