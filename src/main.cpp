
// #include <Arduino.h>
#include <bluefruit.h>

int generation;
int ruleset[] = {0, 1, 1, 1, 1, 0, 0, 0};
int setA[8];
int setB[8];
int *setC;
int *current;
int *next;

void setup()
{
  Serial.begin(115200);
  while (!Serial)
  {
    delay(10);
  }

  // for (int i = 0; i < 8; i++)
  // {
  //   setA[i] = 0;
  // }
  // setA[8 / 2] = 1;
  // generation = 0;
  // current = setA;
  // next = setB;
}

void generate()
{
  for (int i = 0; i < 8; i++)
  {
    Serial.print(current[i], DEC);
  }
  Serial.println();

  for (int i = 0; i < 8; i++)
  {
    int left = current[((i - 1) + 8) % 8];
    int center = current[i];
    int right = current[(i + 1) % 8];

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
  Serial.println("HelloWorld");
  // generate();
}
