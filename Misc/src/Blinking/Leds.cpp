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
            //this->ledLarge = new TKLed(O4);
            this->tempSensor=new TKThermistor(I1);      
            Serial.begin(115200);      
        }
        void process()
        {
            //this->ledLarge->blink(100,200);
            float tempInC=this->tempSensor->readCelsius();
            Serial.println(tempInC);
            delay(10000);
        }
};