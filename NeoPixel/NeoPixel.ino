#include "src/RotatingColor/RotatingColor.h"
//#include "src/RotatingRainbow/RotatingRainbow.h"
#include "src/SnowFall/SnowFall.cpp"
#include "src/Sequencer/Sequencer.cpp"
#include "src/Gradient/Gradient.cpp"

 RotatingColor *rotatingColor;
//RotatingRainbow *rotatingRainbow;
SnowFall *snowFall;
Sequencer *sequencer;
Gradient *gradient;

void setup()
{
   rotatingColor = new RotatingColor(20,114);
   //rotatingRainbow = new RotatingRainbow(800, 2000);
   snowFall = new SnowFall();
   sequencer=new Sequencer();
   gradient=new Gradient();
}

void loop()
{
   //rotatingColor->process(true);
   // rotatingRainbow->process();
   snowFall->process();
  // sequencer->process();
   //gradient->process();
}
