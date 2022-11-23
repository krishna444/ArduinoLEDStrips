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
            this->tempSensor = new TKThermistor(I1);
            Serial.begin(115200);
        }
        void process()
        {
            float tempCelcius=this->tempSensor->readCelsius();
            Serial.print(tempCelcius);
            Serial.print("\t\t");
            delay(10000); 
        }
};