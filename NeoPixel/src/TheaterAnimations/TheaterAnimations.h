#include<Arduino.h>
#include<Adafruit_NeoPixel.h>
/**
 * Code copied from: https://github.com/adafruit/Adafruit_NeoPixel/blob/master/examples/strandtest_wheel/strandtest_wheel.ino
*/
#define PIN 7
#define NUMPIXELS 20
//#define LIGHT_THRESHOLD 40

class TheaterAnimations
{
    private:
        int delay_millis;
        Adafruit_NeoPixel strip;
        void colorWipe(uint32_t c, uint8_t wait);
        void rainbow(uint8_t wait);
        void rainbowCycle(uint8_t wait);
        void theaterChase(uint32_t c, uint8_t wait);
        void theaterChaseRainbow(uint8_t wait);
        uint32_t Wheel(byte WheelPos);
    
    public:
        TheaterAnimations();
        TheaterAnimations(uint8_t delay);
        void init();
        void process();        
};