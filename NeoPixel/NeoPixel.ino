#include "src/RotatingColor/RotatingColor.h"
//#include "src/RotatingRainbow/RotatingRainbow.h"
//#include "src/SnowFall/SnowFall.cpp"
#include "src/Sequencer/Sequencer.cpp"
#include "src/Gradient/Gradient.cpp"
#include "src/TheaterAnimations/TheaterAnimations.h"

 RotatingColor *rotatingColor;
//RotatingRainbow *rotatingRainbow;
// SnowFall *snowFall;
Sequencer *sequencer;
Gradient *gradient;
TheaterAnimations* theaterAnimations;

void setup()
{
   rotatingColor = new RotatingColor(20,114);
   //rotatingRainbow = new RotatingRainbow(800, 2000);
   // snowFall = new SnowFall();
   sequencer=new Sequencer();
   gradient=new Gradient();
   theaterAnimations=new TheaterAnimations();
}

void loop()
{
   //rotatingColor->process(false);
   // rotatingRainbow->process();
   // snowFall->process();
   //sequencer->process();
   //gradient->process();
   theaterAnimations->process();
}
