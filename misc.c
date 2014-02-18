/* 
** misc.h
** 1996/02/11
**
** Copyright 1996, Christopher Osburn, Lunar Outreach Services, 
** Non-commercial usage license granted to all.
**
** Miscellaneous routines for moon phase programs
**
*/

#include "moon.h"
#include <math.h>

extern double torad(double x)
/* convert x to radians */
{
  x = fmod(x, 360.0); /* normalize the angle */
  return ((x) * 0.01745329251994329576);
                    /* and return the result */
}

