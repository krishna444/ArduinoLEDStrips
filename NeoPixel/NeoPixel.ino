#include "src/RotatingColor/RotatingColor.h"
//#include "src/RotatingRainbow/RotatingRainbow.h"

RotatingColor *rotatingColor;
//RotatingRainbow *rotatingRainbow;


void setup()
{  
    rotatingColor = new RotatingColor(); 
//    rotatingRainbow=new RotatingRainbow(80,200);
}

void loop()
{    
    rotatingColor->process();    
//    rotatingRainbow->process();

}
