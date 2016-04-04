#ifndef Plantokei_Music_h
#define Plantokei_Music_h

#include "Arduino.h"

#define c 3830    // 261 Hz
#define d 3400    // 294 Hz
#define e 3038    // 329 Hz
#define f 2864    // 349 Hz
#define g 2550    // 392 Hz
#define a 2272    // 440 Hz
#define b 2028    // 493 Hz
#define C 1912    // 523 Hz
#define R 0 // Define a special note, 'R', to represent a rest

class PlantokeiMusic
{
  public:
    PlantokeiMusic(int pin);
    void playTone();
    void playSong();

  private:
    int _pin;
};

#endif