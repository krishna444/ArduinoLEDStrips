#include "../../src/TinkerKat/TinkerKit.h"
#include <math.h>
class SensorsInfo
{
private:
    TKLightSensor *lightSensor;
    TKThermistor *tempSensor;

public:
    float temp=0;
    float light=0;
    float prevTemp = 0;
    float prevLight = 0;
    SensorInfo()
    {
        this->tempSensor = new TKThermistor(I1);
        this->lightSensor = new TKLightSensor(I0);
        Serial.begin(115200);
    }

     void process()
     {
        temp = this->tempSensor->readCelsius();
        light = this->lightSensor->read();

        if (abs(temp - prevTemp) > 0.0)
        {
            Serial.print("temp:");
            Serial.print(temp);
            Serial.print(";");
            Serial.print("light:");
            Serial.println(light);
            prevTemp = temp;
            prevLight =light;
        }
        delay(1000);
     }
};