//#include "src/RotatingColor/RotatingColor.h"
//#include "src/RotatingRainbow/RotatingRainbow.h"
#include "src/SnowFall/SnowFall.cpp"


//RotatingColor *rotatingColor;
//RotatingRainbow *rotatingRainbow;
SnowFall *snowFall;


void setup()
{  
    //rotatingColor = new RotatingColor(); 
    //rotatingRainbow=new RotatingRainbow(80,200);
     snowFall=new SnowFall();
     //snowFall->init();
}

void loop()
{    
    //rotatingColor->process();    
//    rotatingRainbow->process();
snowFall->process();

}
