#include <Arduino.h>
class BlinkingNew
{
protected:
    uint8_t pin;
    uint16_t on_delay;
    uint16_t off_delay;

public:
    BlinkingNew(uint8_t _pin, uint16_t _on_delay, uint16_t _off_delay)
    {
        pin = _pin;
        on_delay = _on_delay;
        off_delay = _off_delay;
    }
    void blink()
    {
        digitalWrite(this->pin, HIGH);
        delay(this->on_delay);
        digitalWrite(this->pin, LOW);
        delay(this->off_delay);
    }
};