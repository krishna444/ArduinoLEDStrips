#include "src/RotatingColor/RotatingColor.h"
#include "src/RotatingRainbow/RotatingRainbow.h"
#include "src/SnowFall/SnowFall.cpp"
#include "src/Sequencer/Sequencer.cpp"
#include "src/Gradient/Gradient.cpp"
#include "src/TheaterAnimations/TheaterAnimations.h"

 RotatingColor *rotatingColor;
RotatingRainbow *rotatingRainbow;
SnowFall *snowFall;
Sequencer *sequencer;
Gradient *gradient;
TheaterAnimations* theaterAnimations;

void setup()
{
   rotatingColor = new RotatingColor(500,1500);
<<<<<<< HEAD
   //rotatingRainbow = new RotatingRainbow(800, 2000);
=======
   rotatingRainbow = new RotatingRainbow(800, 2000);
>>>>>>> dc170ca111a288b1be522aa1c64b91f872760520
   snowFall = new SnowFall();
   sequencer=new Sequencer();
   gradient=new Gradient();
   theaterAnimations=new TheaterAnimations();
}

void loop()
{
   rotatingColor->process(false);
   // rotatingRainbow->process();
   // snowFall->process();
   //sequencer->process();
   //gradient->process();
   //theaterAnimations->process();
}
