

#include <Arduino.h>
// #include <bluefruit.h>
#include <FastLED.h>

#define LED_PIN_COUNT 8
#define ROW_LENGTH (5*LED_PIN_COUNT)

CRGB leds[ROW_LENGTH];

int generation;
int ruleset[] = {0, 1, 1, 1, 1, 0, 0, 0};
int setA[ROW_LENGTH];
int setB[ROW_LENGTH];
int *setC;
int *current;
int *next;

void setup()
{
  {
    CRGB* ledPtr = leds;
    FastLED.addLeds<NEOPIXEL, 21>(ledPtr, ROW_LENGTH); ledPtr += 5;
    FastLED.addLeds<NEOPIXEL, 18>(ledPtr, ROW_LENGTH); ledPtr += 5;
    FastLED.addLeds<NEOPIXEL, 6>(ledPtr, ROW_LENGTH); ledPtr += 5;
    FastLED.addLeds<NEOPIXEL, 3>(ledPtr, ROW_LENGTH); ledPtr += 5;
    FastLED.addLeds<NEOPIXEL, 5>(ledPtr, ROW_LENGTH); ledPtr += 5;
    FastLED.addLeds<NEOPIXEL, 2>(ledPtr, ROW_LENGTH); ledPtr += 5;
    FastLED.addLeds<NEOPIXEL, 17>(ledPtr, ROW_LENGTH); ledPtr += 5;
    FastLED.addLeds<NEOPIXEL, 15>(ledPtr, ROW_LENGTH);
  }
  

  for (int i = 0; i < ROW_LENGTH; i++)
  {
    setA[i] = 0;
  }
  setA[ROW_LENGTH / 2] = 1;
  generation = 0;
  current = setA;
  next = setB;
  Serial.begin(115200);
  // while (!Serial)
  // {
  //   delay(10);
  // }
  
}

void generate()
{
  for (int i = 0; i < ROW_LENGTH; i++)
  {
    if (current[i]) {
      leds[i].r = 255;
    } else {
      leds[i].r = 0;
    }
    leds[i].g = 0;
    leds[i].b = 0;
  }
  delay(150);
  FastLED.show();

  for (int i = 0; i < ROW_LENGTH; i++)
  {
    Serial.print(current[i], DEC);
  }
  Serial.println();

  for (int i = 0; i < ROW_LENGTH; i++)
  {
    int left = current[((i - 1) + ROW_LENGTH) % ROW_LENGTH];
    int center = current[i];
    int right = current[(i + 1) % ROW_LENGTH];

    //This "left<<2 | center<<1 | right" gives you a Dec value, eg. 7 which is 111...
    //Then it looks up in the index i to find the rule
    next[i] = ruleset[(left << 2) | (center << 1) | right];
  }
  //setC  is assigned the address of the each element in setA
  setC = current;
  //swap each elements in each array
  current = next;
  next = setC;

  generation++;
}

void loop()
{
  generate();
  // Serial.print("HelloWorld");
}