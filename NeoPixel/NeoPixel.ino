//#include "src/RotatingColor/RotatingColor.h"
#include "src/RotatingRainbow/RotatingRainbow.h"
//#include "src/SnowFall/SnowFall.cpp"

// RotatingColor *rotatingColor;
RotatingRainbow *rotatingRainbow;
// SnowFall *snowFall;

void setup()
{
   //  rotatingColor = new RotatingColor();
   rotatingRainbow = new RotatingRainbow(800, 2000);
   // snowFall = new SnowFall();
}

void loop()
{
   // rotatingColor->process();
   rotatingRainbow->process();
   // snowFall->process();
}
