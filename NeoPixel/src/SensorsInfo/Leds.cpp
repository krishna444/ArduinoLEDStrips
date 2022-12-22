#include "../../src/TinkerKat/TinkerKit.h"
#include <Adafruit_NeoPixel.h>
#include <Arduino.h>
#include <math.h>
#define NUMPIXELS 20
#define PIN 7

class Leds
{
private:
    TKLed *ledRed;
    TKLed *ledGreen;
    TKLed *ledBlue;
    TKLed *ledLarge;
    TKLightSensor *lightSensor;
    TKThermistor *tempSensor;
    Adafruit_NeoPixel strip;
    int selectedPixel = 0;
    struct SensorInfo
    {
        float temp;
        float light;
    } sensorInfo;
    String incomingString;
    float prevTemp = 0;
    float prevLight = 0;

public:
    Leds()
    {
        this->tempSensor = new TKThermistor(I1);
        this->lightSensor = new TKLightSensor(I0);
        //strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
        //strip.begin();
        Serial.begin(115200);
    }
    void process()
    {
        float tempCelcius = this->tempSensor->readCelsius();
        float light = this->lightSensor->read();

        if (abs(tempCelcius - prevTemp) > 0.0)
        {
            Serial.print("temp:");
            Serial.print(tempCelcius);
            Serial.print(";");
            Serial.print("light:");
            Serial.println(light);
            prevTemp = tempCelcius;
            prevLight = light;

            /*int red = (int)(tempCelcius < 18.0 ? 0 : tempCelcius > 22.0 ? 255
                                                                        : map(tempCelcius, 18.0, 22.0, 0, 255));

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
            strip.show();*/
        }

        /*if (Serial.available() > 0)
        {
            # read the incoming text
            incomingString = Serial.readString();
            if (incomingString == "sensors")
            {
                sensorInfo.light = light;
                sensorInfo.temp = tempCelcius;
                Serial.print("temp:");
                Serial.print(sensorInfo.temp);
                Serial.print(";");
                Serial.print("light:");
                Serial.println(sensorInfo.light);
            }
        }*/

        delay(1000);
    }
};
