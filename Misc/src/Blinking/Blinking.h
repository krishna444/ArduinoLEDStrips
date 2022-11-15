class Blinking
{
    public:
        Blinking(uint8_t _pin);
        Blinking(uint8_t _pin, uint16_t delay);
        Blinking(uint8_t _pin, uint16_t _on_delay, uint16_t _off_delay);     
        void blink();
    protected:
        uint8_t pin;
        uint16_t on_delay;
        uint16_t off_delay;
};