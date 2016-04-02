void setup() {
  Serial.begin(9600);
  Serial.println("hello!");
}

void loop() {
  Serial.println("ugh");
}

// #define sclk 4
// #define mosi 5
// #define cs   6
// #define dc   7
// #define rst  8  // you can also connect this to the Arduino reset
// #define photocell 0

// #include <Adafruit_GFX.h>    // Core graphics library
// #include <Adafruit_ST7735.h> // Hardware-specific library
// #include <SPI.h>

// #if defined(__SAM3X8E__)
//     #undef __FlashStringHelper::F(string_literal)
//     #define F(string_literal) string_literal
// #endif

// // Use low-speed display
// Adafruit_ST7735 tft = Adafruit_ST7735(cs, dc, mosi, sclk, rst);

// float p = 3.1415926;

// bool SUN_FILLS[] = {false, false, false, false, false};

// int SUN_RADIUS = 5;
// int SUN_PADDING = 2;

// int LINE_HEIGHT = 10; // pixels

// int LINE_SUNS = 10 * LINE_HEIGHT;

// void setup(void) {
//   Serial.begin(9600);
//   Serial.println("hello!");

//   tft.initR(INITR_BLACKTAB);
//   tft.fillScreen(ST7735_BLACK);
//   initSuns();
// }

// void loop() {
//   int lightLevel = getLightLevel();
//   printLumens(lightLevel);
//   delay(100);
// }

// int getLightLevel() {
//   float photocellReading = (float) analogRead(photocell);
//   int lightLevel = floor((photocellReading / 1023) * 5);
//   return lightLevel;
// }

// void initSuns() {
//   for (int i = 1; i <= 5; i++) {
//     printSun(i, false);
//   }
// }

// void printLumens(int lightLevel) {
//   for (int i = 1; i <= 5; i++) {
//     bool hasFill = i <= lightLevel;
//     bool hadFill = SUN_FILLS[i-1];

//     if(hasFill != hadFill) {
//       printSun(i, hasFill);
//     }

//     SUN_FILLS[i-1] = hasFill;
//   }
// }

// void printSun(int i, bool fill) {
//   int j = i - 1;
//   int outlineX = 28 + (j * SUN_RADIUS * 2) + SUN_RADIUS + (j * SUN_PADDING);

//   if (fill) {
//     tft.fillCircle(outlineX, LINE_SUNS, SUN_RADIUS, ST7735_YELLOW);
//   } else {
//     tft.fillCircle(outlineX, LINE_SUNS, SUN_RADIUS, ST7735_BLACK);
//   }

//   tft.drawCircle(outlineX, LINE_SUNS, SUN_RADIUS, ST7735_YELLOW);
// }

