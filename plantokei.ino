#define sclk 4
#define mosi 5
#define cs   6
#define dc   7
#define rst  8  // you can also connect this to the Arduino reset

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// Use low-speed display
Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

float p = 3.1415926;

int SUN_RADIUS = 5;
int SUN_PADDING = 2;

int LINE_HEIGHT = 10; // pixels

int LINE_SUNS = 10 * LINE_HEIGHT;

void setup(void) {
  Serial.begin(9600);
  Serial.print("hello!");
  
  tft.initR(INITR_BLACKTAB); 
  tft.fillScreen(ST7735_BLACK);
}

void loop() {
  printLumens();
  delay(500);
}

void printLumens() {
  printSun(0, true);
  printSun(1, true);
  printSun(2, true);
  printSun(3, false);
  printSun(4, false);
}

void printSun(int i, bool fill) {
  int outlineX = (i * SUN_RADIUS * 2) + SUN_RADIUS + (i * SUN_PADDING);
  int outlineY = 10 * LINE_HEIGHT;
  tft.drawCircle(outlineX, outlineY, SUN_RADIUS, ST7735_YELLOW);

  if (fill) {
    tft.fillCircle(outlineX, outlineY, SUN_RADIUS, ST7735_YELLOW);
  }
}

