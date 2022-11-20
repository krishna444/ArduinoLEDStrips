#include "TinkerKat/TinkerKit.h"

class Leds
{
    private:
        TKLed *ledRed;
        TKLed *ledGreen;
        TKLed *ledBlue;
        TKLed *ledLarge;
    public:
        Leds()
        {
            this->ledLarge = new TKLed(O4);
            this->ledRed=new TKLed(O5);
            this->ledGreen=new TKLed(O2);
            this->ledLarge->brightness(255);
            this->ledRed->brightness(255);
            this->ledGreen->brightness(255);
            
        }
        void process()
        {            
            this->ledLarge->blink(100);
            this->ledRed->blink(200);
            this->ledGreen->blink(300);            
        }
};