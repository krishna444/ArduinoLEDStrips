#include "src/RotatingColor/RotatingColor.h"
//#include "src/RotatingRainbow/RotatingRainbow.h"
//#include "src/SnowFall/SnowFall.cpp"
#include "src/Sequencer/Sequencer.cpp"

 RotatingColor *rotatingColor;
//RotatingRainbow *rotatingRainbow;
// SnowFall *snowFall;
Sequencer *sequencer;

void setup()
{
   rotatingColor = new RotatingColor(20,114);
   //rotatingRainbow = new RotatingRainbow(800, 2000);
   // snowFall = new SnowFall();
   sequencer=new Sequencer();
}

void loop()
{
   //rotatingColor->process(false);
   // rotatingRainbow->process();
   // snowFall->process();
   sequencer->process();
}
