/*
** moon.h
**
** Headers and function defs for moon phase routines
**
** Copyright 1996, Christopher Osburn, Lunar Outreach Services, 
**
** This program is free software: you can redistribute it and/or modify
** it under the terms of the GNU Lesser General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU Lesser General Public License for more details.
**
** You should have received a copy of the GNU Lesser General Public License
** along with this program.  If not, see <http://www.gnu.org/licenses/>.
** 
**
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
