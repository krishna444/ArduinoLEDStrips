#include "RotatingColor.h"

int colors[][3] = {
    {148, 0, 211}, // Voilet
    {75, 0, 130},  // Indigo
    {0, 0, 255},   // Blue
    {0, 255, 0},   // Green
    {255, 255, 0}, // Yellow
    {255, 127, 0}, // Orange
    {255, 0, 0}    // Red
};
const int NCOLOURS = sizeof(colors) / sizeof(*colors);

RotatingColor::RotatingColor() : RotatingColor(MIN_DELAY, MAX_DELAY)
{
}
RotatingColor::RotatingColor(uint16_t _delay) : RotatingColor(_delay, _delay)
{
}
RotatingColor::RotatingColor(uint16_t _min_delay, uint16_t _max_delay)
{
    this->strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
    //this->lightSensor = new TKLightSensor(I0);
    this->thermistor = new TKThermistor(I1);
    min_delay = _min_delay;
    max_delay = _max_delay;
    Serial.begin(115200);
    strip.begin();
    delay_millis = random(min_delay, max_delay);
    colorIndex = 0;
}

void RotatingColor::process(boolean _multi_direction, boolean _temperature)
{
    _multi_direction ? this->multiDirection() : this->singleDirection(_temperature);
}

void RotatingColor::singleDirection(bool temp = false)
{
    float light = 10;//lightSensor->read();
    //delay(10);
    float tempC = thermistor->readCelsius();    
    delay(500);
    Serial.print("Light=");Serial.print(light);Serial.print("\t");Serial.print("Temp=");Serial.println(tempC);
    if (light > LIGHT_THRESHOLD)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    }
    strip.clear();
    if (!temp)
    {
        strip.setPixelColor(selectedPixel, colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
        strip.setPixelColor((selectedPixel + NUMPIXELS / 2) % NUMPIXELS, colors[(colorIndex + 1) % NCOLOURS][0], colors[(colorIndex + 1) % NCOLOURS][1], colors[(colorIndex + 1) % NCOLOURS][2]);
    }
    else
    {
        float tempC = this->thermistor->readCelsius();    
        Serial.print("Light=");Serial.print(light);Serial.print("\t");Serial.print("Temp=");Serial.println(tempC);
        int red = (int)(tempC < 18.0 ? 0 : tempC > 22.0 ? 255
                                                        : map(tempC, 18.0, 22.0, 0, 255));
        int green = 0;
        int blue = 255 - red;
        strip.setPixelColor(selectedPixel, red, green, blue);
        strip.setPixelColor((selectedPixel + NUMPIXELS / 2) % NUMPIXELS, red, green, blue);
    }
    selectedPixel++;
    if (selectedPixel >= NUMPIXELS)
    {
        selectedPixel = 0;
        colorIndex++;
        if (colorIndex >= NCOLOURS)
        {
            colorIndex = 0;
        }
        delay_millis = random(min_delay, max_delay);
    }

    strip.show();
    delay(delay_millis);
}

void RotatingColor::multiDirection()
{
    float light = lightSensor->read();    
    Serial.print(light);
    if (light > LIGHT_THRESHOLD)
    {
        strip.clear();
        strip.show();
        delay(2000);
        return;
    }
    strip.clear();
    strip.setPixelColor(selectedPixel, colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    strip.setPixelColor((selectedPixel + NUMPIXELS / 2) % NUMPIXELS, colors[(colorIndex + 1) % NCOLOURS][0], colors[(colorIndex + 1) % NCOLOURS][1], colors[(colorIndex + 1) % NCOLOURS][2]);
    forwardDirection ? selectedPixel++ : selectedPixel--;

    if (selectedPixel >= NUMPIXELS || selectedPixel <= 0)
    {
        forwardDirection = !forwardDirection;
        colorIndex++;
        if (colorIndex >= NCOLOURS)
        {
            colorIndex = 0;
        }
        delay_millis = random(min_delay, max_delay);
    }

    strip.show();
    delay(delay_millis);
}
