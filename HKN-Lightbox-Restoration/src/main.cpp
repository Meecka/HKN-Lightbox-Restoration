#include <Adafruit_NeoPixel.h>

#define LED_PIN 3
#define NUM_LEDS 169

// Switch pins
const uint8_t switchPins[] = {9, 10, 11, 12, 13};
const uint8_t NUM_SWITCHES = 5;

// Segment structure
struct Segment
{
  uint16_t start;
  uint16_t end;
};

// LED segments mapped to switches (same order)
const Segment segments[NUM_SWITCHES] = {
    {139, 169}, // TOP
    {40, 72},   // LEFT
    {72, 111},  // MIDDLE
    {111, 139}, // RIGHT
    {0, 40}     // BOTTOM
};

Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_RGBW + NEO_KHZ800);

// Colors
uint32_t WHITE;
uint32_t OFF;

void setup()
{
  // Initialize switch pins
  for (uint8_t i = 0; i < NUM_SWITCHES; i++)
  {
    pinMode(switchPins[i], INPUT_PULLUP);
  }

  strip.begin();

  // Initialize colors AFTER strip.begin()
  WHITE = strip.Color(0, 0, 0, 255);
  OFF = strip.Color(0, 0, 0, 0);

  strip.show(); // Turn everything off
}

void loop()
{
  for (uint8_t i = 0; i < NUM_SWITCHES; i++)
  {
    bool isPressed = (digitalRead(switchPins[i]) == LOW);
    uint32_t color = isPressed ? WHITE : OFF;

    for (uint16_t led = segments[i].start; led < segments[i].end; led++)
    {
      strip.setPixelColor(led, color);
    }
  }

  strip.show();
}