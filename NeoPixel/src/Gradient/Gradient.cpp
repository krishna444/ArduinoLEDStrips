#include <Adafruit_NeoPixel.h>
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
#define LIGHT_THRESHOLD 50

class Gradient
{
private:
    // Instatiate the NeoPixel from the ibrary
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    // initial colors, you can change these
    int red = 100;
    int blue = 255;

    // variable delay time
    int delayTime = 15;

    // stores the start time, use unsignged long to prevent overflow
    unsigned long startTime;

    int startPixel = 0;

public:
    Gradient()
    {
        Serial.begin(115200);
        strip.begin();
        strip.show(); // Initialize all pixels to 'off'

        startTime = millis();
        activate();
    }

    void process()
    {        
        delayTime = 190;    

        if (startTime + delayTime < millis())
        {
            activate();
            startTime = millis();
        }
    }

    void activate()
    {
        int sp = startPixel;

        for (int i = 0; i < NUMPIXELS; i++)
        {
            int green=map(i,0,NUMPIXELS,0,255);
            
            strip.setPixelColor(sp, 0, green, 0);

            if (sp == NUMPIXELS)
                sp = 0;
            else
                sp++;
        }

        strip.show();

        startPixel++;
        if (startPixel == NUMPIXELS)
            startPixel = 0;
    }
};