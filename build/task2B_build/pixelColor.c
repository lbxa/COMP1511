/*
 *  pixelColor.c
 *  mandelbrot colors | Lucas Barbosa & Jordan Hyunh
 *
 *  Created by Richard Buckland on 13/04/11.
 *  Licensed under Creative Commons SA-BY-NC 3.0.  
 *
 *  Primary theme : MAGIC_NUMBER  25
 *
 */

#include "pixelColor.h"

#define MAX_INTENSITY  255
#define MIN_INTENSITY  0
#define MAGIC_NUMBER   25
#define COLOR_CONSTANT 8
#define WHITE          0xFF
#define GREY           0xCCCCCC
#define BLACK          0x000000
#define LIGHTGREY      0x999999

unsigned char stepsToRed (int steps) {
  unsigned char returnColor = steps;
  returnColor -= GREY;
  returnColor += MAGIC_NUMBER;
  returnColor *= COLOR_CONSTANT;
  if (steps >= MAX_INTENSITY) {
    returnColor = WHITE;
  }
  return returnColor;
}

unsigned char stepsToBlue (int steps) {
  unsigned char returnColor = steps;
  returnColor -= BLACK;
  returnColor *= MAGIC_NUMBER;
  returnColor *= COLOR_CONSTANT;
  if (steps >= MAX_INTENSITY) {
    returnColor = WHITE;
  }
  return returnColor;
}

unsigned char stepsToGreen (int steps) {
  unsigned char returnColor = steps;
  returnColor -= LIGHTGREY;
  returnColor -= MAGIC_NUMBER;
  returnColor *= COLOR_CONSTANT;
  if (steps >= MAX_INTENSITY) {
    returnColor = WHITE;
  }
  return returnColor;
}