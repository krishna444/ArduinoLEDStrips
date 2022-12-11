//#include "src/Blinking/Blinking.h"
//#include "src/Blinking/BlinkingNew.cpp"
#include "src/Blinking/Leds.cpp"
//Blinking blinking(13);
//BlinkingNew blinkingnew(13,100,100);
Leds *leds;
void setup()
{    
    leds=new Leds();
}

void loop()
{
    //blinkingnew.blink();    
    leds->process();
}