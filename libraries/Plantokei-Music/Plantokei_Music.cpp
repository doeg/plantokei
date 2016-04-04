// The current iteration of this code is largely thanks to
// http://www.arduino.cc/en/Tutorial/PlayMelody
#include "Arduino.h"
#include "Plantokei_Music.h"

// Music
int melody[] = { c, e, g, C };
int beats[] = { 8, 4, 4, 8 };
int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
int tone_ = 0;
int beat = 0;
long duration  = 0;
long tempo = 10000;
int pause = 1000; // Set length of pause between notes
int rest_count = 100; // Loop variable to increase Rest length

PlantokeiMusic::PlantokeiMusic(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void PlantokeiMusic::playSong() {
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

void PlantokeiMusic::playTone() {
  long elapsed_time = 0;

  if (tone_ > 0) { // if this isn't a Rest beat, while the tone has
    //  played less long than 'duration', pulse speaker HIGH and LOW
    while (elapsed_time < duration) {

      digitalWrite(_pin, HIGH);
      delayMicroseconds(tone_ / 2);

      // DOWN
      digitalWrite(_pin, LOW);
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
