#define PROD
#ifdef PROD
#include "src/TinkerKat/TinkerKit.h"
#endif
#include "src/RotatingColor/RotatingColor.h"
#define LIGHT_THRESHOLD 40

#ifdef PROD
TKLightSensor lightSensor(I0);
#endif

RotatingColor rotatingColor;

void setup()
{    
}

void loop()
{
    #ifdef PROD
    float light = lightSensor.read();
    if (light > LIGHT_THRESHOLD)
    {
        //strip.clear();
        //strip.show();
        delay(2000);
        return;
    }
    #endif
    rotatingColor.process();    
}
