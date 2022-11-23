#include "TinkerKat/TinkerKit.h"

class Leds
{
    private:
        TKLed *ledRed;
        TKLed *ledGreen;
        TKLed *ledBlue;
        TKLed *ledLarge;
        TKThermistor *tempSensor;
    public:
        Leds()
        {
            this->ledLarge = new TKLed(O4);
        }
        void process()
        {
            this->ledLarge->blink(100,200);
        }
};