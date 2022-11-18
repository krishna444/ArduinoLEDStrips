#include <Adafruit_NeoPixel.h>
#include <math.h>
#define PIN 7
#define NUMPIXELS 20
#define LIGHT_THRESHOLD 50

class Sequencer
{
private:
    Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    // initial colors, you can change these
    int red = 100;
    int blue = 255;
    int green = 255;
    // stores the start time, use unsignged long to prevent overflow
    unsigned long startTime;

    // variable delay time
    int delayTime = 20;

    // start pixel, use for gradients
    int startPixel = 0;
    // for brightness
    int brightness = 255;
    int brightDirection = -10;

    // modulus variable
    int xmasMod = 0;

    // which sequence we are using and the max # of sequences
    int sequenceNum = 0;
    int numSequences = 5;

public:
    Sequencer()
    {
        Serial.begin(115200);
        strip.begin(); // initialize the strip
        strip.show();  // make sure it is visible
        strip.clear(); // Initialize all pixels to 'off'

        startTime = millis();
        activate();

        // seed the random number generator with whatever noise is on pin A0 (we don't have anything connected here)
        randomSeed(analogRead(0));
    }
    void process()
    {
        // int sensorValue = analogRead(sensorPin);
        delayTime = 1000;
        // startTime = 0;
        switchSequence();
        if (startTime + delayTime < millis())
        {
            activate();
            startTime = millis();
        }

        /*if (digitalRead(switchPin) == true)
        {
            bSwitchDown = true;
            startTime = 0;
            delay(10); // debounce
        }
        else
        {
            if (bSwitchDown)
            {
                // first release of switch
                bSwitchDown = false;
                switchSequence();
            }

            if (startTime + delayTime < millis())
            {
                activate();
                startTime = millis();
            }
        }*/
    }
    // call appropiate function based on sequence number
    void activate()
    {
        if (sequenceNum == 0)
            sequenceGradient();
        else if (sequenceNum == 1)
            sequenceSoloMover();
        else if (sequenceNum == 2)
            sequenceBrightShift();
        else if (sequenceNum == 3)
            sequenceRandom();
        else if (sequenceNum == 4)
            sequenceXmas();
    }
    // switch to an new random sequence
    int switchSequence()
    {
        int currentNum = sequenceNum;

        // this while loop ensures that we don't repeat the current sequence
        while (currentNum == sequenceNum)
            sequenceNum = random(numSequences);

        strip.setBrightness(brightness);

        return sequenceNum;
    }

    //---------  SEQUENCE GRADIENT FUNCITONS -------------//
    void sequenceGradient()
    {
        int sp = startPixel;

        for (int i = 0; i < NUMPIXELS; i++)
        {
            strip.setPixelColor(sp, i * 4, 0, blue);

            if (sp == NUMPIXELS)
                sp = 0;
            else
                sp++;
        }

        strip.show();

        startPixel++;
        if (startPixel == 60)
            startPixel = 0;
    }

    //---------  SEQUENCE SOLO MOVER: a single pixel moves around the strip -------------//
    void sequenceSoloMover()
    {
        for (int i = 0; i < NUMPIXELS; i++)
        {
            if (i == startPixel)
                strip.setPixelColor(i, 255, 0, 0);
            else
                strip.setPixelColor(i, 0, 255, 255);
        }

        strip.show();

        startPixel++;
        if (startPixel == NUMPIXELS)
            startPixel = 0;
    }

    //---------  SEQUENCE BRIGHT SHIFT: brightness fades up/down -------------//
    void sequenceBrightShift()
    {
        for (int i = 0; i < NUMPIXELS; i++)
            strip.setPixelColor(i, 255, 0, 0);

        strip.setBrightness(brightness);
        strip.show();

        brightness = brightness + brightDirection;
        if (brightness < 0)
        {
            brightness = 0;
            brightDirection = -brightDirection;
        }
        else if (brightness > 255)
        {
            brightness = 255;
            brightDirection = -brightDirection;
        }
    }

    //---------  SEQUENCE RANDOM: Each pixel is a random color -------------//
    void sequenceRandom()
    {
        for (int i = 0; i < NUMPIXELS; i++)
            strip.setPixelColor(i, random(255), random(255), random(255));

        strip.show();
    }

    //---------  SEQUENCE XMAS: Alternate green and red pixels -------------//
    void sequenceXmas()
    {
        for (int i = 0; i < NUMPIXELS; i++)
        {
            if (i % 2 == xmasMod)
                strip.setPixelColor(i, 255, 0, 0);
            else
                strip.setPixelColor(i, 0, 255, 0);
        }

        if (xmasMod == 0)
            xmasMod = 1;
        else
            xmasMod = 0;

        strip.show();
    }
};