#include "src/RotatingColor/RotatingColor.h"
//#include "src/RotatingRainbow/RotatingRainbow.h"
//#include "src/SnowFall/SnowFall.cpp"

 RotatingColor *rotatingColor;
//RotatingRainbow *rotatingRainbow;
// SnowFall *snowFall;

void setup()
{
   rotatingColor = new RotatingColor(20,114);
   //rotatingRainbow = new RotatingRainbow(800, 2000);
   // snowFall = new SnowFall();
}

void loop()
{
   rotatingColor->process(false);
   // rotatingRainbow->process();
   // snowFall->process();
}
