#include "TinkerKat/TinkerKit.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#define NUMPIXELS 20
#define PIN 7

class Leds
{
    private:
        TKLed *ledRed;
        TKLed *ledGreen;
        TKLed *ledBlue;
        TKLed *ledLarge;
        TKThermistor *tempSensor;
        Adafruit_NeoPixel strip; 
        int selectedPixel=0;
    public:
        Leds()
        {
            this->tempSensor = new TKThermistor(I1);
            strip= Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
            strip.begin();
            Serial.begin(115200);
        }
        void process()
        {
            float tempCelcius=this->tempSensor->readCelsius();
            Serial.print(tempCelcius);            
            int red = (int)(tempCelcius < 18.0 ? 0 : tempCelcius > 22.0 ? 255
                                                        : map(tempCelcius, 18.0, 22.0, 0, 255));
                                                        Serial.print("\tRed:");
                                                        Serial.print(red);
                                                        Serial.print("\t\t");
            int green = 0;
            int blue = 255 - red;
            strip.clear();
            strip.setPixelColor(selectedPixel, red, green, blue);
            strip.setPixelColor((selectedPixel + NUMPIXELS / 2) % NUMPIXELS, red, green, blue);            
            selectedPixel++;
            if (selectedPixel >= NUMPIXELS)
            {
                selectedPixel = 0;
            }
            strip.show();
            delay(1000); 
        }
};