#include "src/Blinking/Blinking.h"
#include "src/Blinking/BlinkingNew.cpp"
//Blinking blinking(13);
BlinkingNew blinkingnew(13,100,100);
void setup()
{    
}

void loop()
{
    blinkingnew.blink();    
}