/*
  Morse.cpp - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/

#include "Arduino.h"
#include "Plantokei_Display.h"

PlantokeiDisplay::PlantokeiDisplay(int pin)
{
  pinMode(pin, OUTPUT);
  _pin = pin;
}

void PlantokeiDisplay::dot()
{
  digitalWrite(_pin, HIGH);
  delay(250);
  digitalWrite(_pin, LOW);
  delay(250);
}

void PlantokeiDisplay::dash()
{
  digitalWrite(_pin, HIGH);
  delay(1000);
  digitalWrite(_pin, LOW);
  delay(250);
}