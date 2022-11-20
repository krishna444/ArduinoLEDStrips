#include "TheaterAnimations.h"

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
const int NCOLOURS = sizeof(COLOURS) / sizeof(*COLOURS);

TheaterAnimations::TheaterAnimations() : TheaterAnimations(50)
{
}

TheaterAnimations::TheaterAnimations(uint8_t delay)
{
    this->delay_millis = delay;
    this->init();
}

void TheaterAnimations::init()
{
    this->strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    this->strip.begin();
    this->strip.setBrightness(50);
    this->strip.show(); // Initialize all pixels to 'off'
}

void TheaterAnimations::process()
{
    for (int i = 0; i < NCOLOURS; i++)
    {
        colorWipe(strip.Color(COLOURS[i][0],COLOURS[i][1],COLOURS[i][2]), 50);  
        colorWipe(strip.Color(255, 10,10), 50);   // Red
        colorWipe(strip.Color(10, 255, 10), 50);   // Green
        colorWipe(strip.Color(10, 10, 255), 50);   // Blue
        colorWipe(strip.Color(128, 128, 128), 50); // White RGBW
    }
    //  Send a theater pixel chase in...
    theaterChase(strip.Color(127, 127, 127), 50); // White
    theaterChase(strip.Color(127, 0, 0), 50);     // Red
    theaterChase(strip.Color(0, 0, 127), 50);     // Blue

    rainbow(20);
    rainbowCycle(20);
    theaterChaseRainbow(50);
}

// Fill the dots one after the other with a color
void TheaterAnimations::colorWipe(uint32_t c, uint8_t wait)
{
    for (uint16_t i = 0; i < strip.numPixels(); i++)
    {
        this->strip.setPixelColor(i, c);
        this->strip.show();
        delay(wait);
    }
}
void TheaterAnimations::rainbow(uint8_t wait)
{
    uint16_t i, j;

    for (j = 0; j < 256; j++)
    {
        for (i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel((i + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

// Slightly different, this makes the rainbow equally distributed throughout
void TheaterAnimations::rainbowCycle(uint8_t wait)
{
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++)
    { // 5 cycles of all colors on wheel
        for (i = 0; i < strip.numPixels(); i++)
        {
            strip.setPixelColor(i, Wheel(((i * 256 / strip.numPixels()) + j) & 255));
        }
        strip.show();
        delay(wait);
    }
}

// Theatre-style crawling lights.
void TheaterAnimations::theaterChase(uint32_t c, uint8_t wait)
{
    for (int j = 0; j < 10; j++)
    { // do 10 cycles of chasing
        for (int q = 0; q < 3; q++)
        {
            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
            {
                strip.setPixelColor(i + q, c); // turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
            {
                strip.setPixelColor(i + q, 0); // turn every third pixel off
            }
        }
    }
}

// Theatre-style crawling lights with rainbow effect
void TheaterAnimations::theaterChaseRainbow(uint8_t wait)
{
    for (int j = 0; j < 256; j++)
    { // cycle all 256 colors in the wheel
        for (int q = 0; q < 3; q++)
        {
            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
            {
                strip.setPixelColor(i + q, Wheel((i + j) % 255)); // turn every third pixel on
            }
            strip.show();

            delay(wait);

            for (uint16_t i = 0; i < strip.numPixels(); i = i + 3)
            {
                strip.setPixelColor(i + q, 0); // turn every third pixel off
            }
        }
    }
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.
uint32_t TheaterAnimations::Wheel(byte WheelPos)
{
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85)
    {
        return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
    }
    if (WheelPos < 170)
    {
        WheelPos -= 85;
        return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
    }
    WheelPos -= 170;
    return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}