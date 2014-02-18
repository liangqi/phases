/*
** moon.h
**
** Headers and function defs for moon phase routines
**
*/

#if !defined __MOON_H
#define __MOON__H

#include <time.h>
#include "jd.h"

extern double moonphasebylunation(int lun, int phi);  /* moonphase.c */
extern double moonphase(double k, int phi);  /* moonphase.c */
extern double torad(double x);              /* misc.c      */

#endif /* __MOON_H */
