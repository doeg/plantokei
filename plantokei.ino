#define sclk 4
#define mosi 5
#define cs   6
#define dc   7
#define rst  8  // you can also connect this to the Arduino reset
#define photocell 0
#define piezo 9

#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978

int  c =    3830;    // 261 Hz
int  d =    3400;    // 294 Hz
int  e =    3038;    // 329 Hz
int  f =    2864;    // 349 Hz
int  g =    2550;    // 392 Hz
int  a =    2272;    // 440 Hz
int  b =    2028;    // 493 Hz
int  C =    1912;    // 523 Hz
int  R =    0; // Define a special note, 'R', to represent a rest

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>

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


int melody[] = { NOTE_C7, NOTE_E7, NOTE_C7, NOTE_G7, NOTE_C6 };
int beats[] = { 16, 8, 8, 8, 32 };

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
