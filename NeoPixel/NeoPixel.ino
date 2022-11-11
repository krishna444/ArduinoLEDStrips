#include <Adafruit_NeoPixel.h>
#include "TinkerKit.h"
#include <math.h>

#define PIN 7

#define NUMPIXELS 20

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

TKLightSensor lightSensor(I0);
//TKButton onOffButton(I1);
//TKPotentiometer potentiometer(I2);

// we want to randomly select from these colours

const int COLOURS[][3] = {
    {255, 128, 64}, //Red
    {64, 255, 64},  //Green
    {64, 64, 255},  //Blue
    {255, 255, 32}, //Yellow
    {255, 64, 255}, //Pink
    {64, 255, 255}, //Cyan
    {255, 255, 255} //White
};

const int NCOLOURS = sizeof(COLOURS) / sizeof(*COLOURS);

// this structure holds the state of the given pixel

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

// we have 4 pixels

struct PixelState pixel[NUMPIXELS];

// I want the pixels to sparkle, so I will use a triangle wave,
// which is to say that they will come on at full brightness and them fade

const unsigned long FADE_TIME_MS = 3000; // three seconds

// the pixels should come on at a random time, To simulate this,
// the pixel will be off for a random amount of time.

const int MIN_OFF_TIME_MS = 1500;
int MAX_OFF_TIME_MS = 3000;
//int delayValue=500;

void setup()
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

void loop()
{
    float light = lightSensor.read();
    Serial.write("Light sensor");
    Serial.print(light);
    Serial.println();
    if (light > 50)
    {
            strip.clear();
            strip.show();
            delay(2000);
            return;
    }
    //int dimmerValue = potentiometer.read();
    //Serial.print("Dimmer");Serial.println(dimmerValue);
    //int button = onOffButton.read();

    for (int i = 0; i < NUMPIXELS; i++)
    {
        //MAX_OFF_TIME_MS = 600;//map(dimmerValue, 0, 1024, 10000, 600);
        if (pixel[i].on)
        {
            // pixel is on
            if (millis() - pixel[i].timeMarkMs >= FADE_TIME_MS)
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
                float brightness = 1 - (millis() - pixel[i].timeMarkMs) / ((float)FADE_TIME_MS);
                brightness = brightness * brightness; //gamma correction

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
