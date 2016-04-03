#define sclk 4
#define mosi 5
#define cs   6
#define dc   7
#define rst  8  // you can also connect this to the Arduino reset
#define photocell 0
#define piezo 9

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include "pitches.h"

void setup();
void loop();
int getLightLevel();
void initSuns();
void printLumens(int lightLevel);
void printSun(int i, bool fill);
void playTone();
void playSong();

#if defined(__SAM3X8E__)
  #undef __FlashStringHelper::F(string_literal)
  #define F(string_literal) string_literal
#endif

// Use low-speed display
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

float p = 3.1415926;

bool SUN_FILLS[] = {false, false, false, false, false};

int SUN_RADIUS = 5;
int SUN_PADDING = 2;

int LINE_HEIGHT = 10; // pixels

int LINE_SUNS = 10 * LINE_HEIGHT;

int melody[] = { c, e, g, C };
int beats[] = { 16, 8, 8, 16 };

int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.

int tone_ = 0;
int beat = 0;
long duration  = 0;
long tempo = 10000;
// Set length of pause between notes
int pause = 1000;
// Loop variable to increase Rest length
int rest_count = 100; //<-BLETCHEROUS HACK; See NOTES

void setup() {
  Serial.begin(9600);
  Serial.println("hello!");

  tft.initR(INITR_BLACKTAB);
  tft.fillScreen(ST7735_BLACK);
  initSuns();

  pinMode(piezo, OUTPUT);
  playSong();
}

void loop() {
  int lightLevel = getLightLevel();
  printLumens(lightLevel);
  delay(100);
}

int getLightLevel() {
  float photocellReading = (float) analogRead(photocell);
  int lightLevel = floor((photocellReading / 1023) * 5);
  return lightLevel;
}

void initSuns() {
  for (int i = 1; i <= 5; i++) {
    printSun(i, false);
  }
}

void printLumens(int lightLevel) {
  for (int i = 1; i <= 5; i++) {
    bool hasFill = i <= lightLevel;
    bool hadFill = SUN_FILLS[i-1];

    if(hasFill != hadFill) {
      printSun(i, hasFill);
    }

    SUN_FILLS[i-1] = hasFill;
  }
}

void printSun(int i, bool fill) {
  int j = i - 1;
  int outlineX = 28 + (j * SUN_RADIUS * 2) + SUN_RADIUS + (j * SUN_PADDING);

  if (fill) {
    tft.fillCircle(outlineX, LINE_SUNS, SUN_RADIUS, ST7735_YELLOW);
  } else {
    tft.fillCircle(outlineX, LINE_SUNS, SUN_RADIUS, ST7735_BLACK);
  }

  tft.drawCircle(outlineX, LINE_SUNS, SUN_RADIUS, ST7735_YELLOW);
}

void playSong() {
  // Set up a counter to pull from melody[] and beats[]
  for (int i=0; i<MAX_COUNT; i++) {
    tone_ = melody[i];
    beat = beats[i];

    duration = beat * tempo; // Set up timing

    playTone();
    // A pause between notes...
    delayMicroseconds(pause);
  }
}

void playTone() {
  long elapsed_time = 0;
  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(piezo,HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(piezo, LOW);
      delayMicroseconds(tone_ / 2);

      // Keep track of how long we pulsed
      elapsed_time += (tone_);
    }
  }
  else { // Rest beat; loop times delay
    for (int j = 0; j < rest_count; j++) { // See NOTE on rest_count
      delayMicroseconds(duration);
    }
  }
}
