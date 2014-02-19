/*
** phases.c:
** 1996/02/11
**
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
** gcc -O -o phases phases.c moonphase.c jd.c misc.c -lm
**
** Calculate 4 cardinal phases for lunations -2003 through
** 2004, output as a table suitable for text searches in
** 5 columns:  Lunation number, time of New Moon, time
** of First Quarter, time of Full Moon, time of Last
** Quarter.  Times given as 1977/02/18 03:37.  So, a 
** sample output record looks like:

+00904 1996/01/20 12:50  1996/01/27 11:14  1996/02/04 15:58  1996/02/12 08:37

** The lunation range covers the years 1923-2084 inclusive.
** the data can be decomposed by columns as:
** Columns  Description
** -------  -------------------------------
**  01      Lunation Number sign
**  02-06   Lunation Number
**  07      <blank>
**  08-11   Year of New Moon
**  12      <slant>
**  13-14   Month of New Moon
**  15      <slant>
**  16-17   Day of New Moon
**  18      <blank>
**  19-20   Hour of New Moon
**  21      <colon>
**  22-23   Minute of New Moon
**  24-25   <blank>
**  26-29   Year of First Quarter
**  30      <slant>
**  31-32   Month of First Quarter
**  33      <slant>
**  34-35   Day of First Quarter
**  36      <blank>
**  37-38   Hour of First Quarter
**  39      <colon>
**  40-41   Minute of First Quarter
**  42-43   <blank>
**  44-47   Year of Full Moon
**  48      <slant>
**  49-50   Month of Full Moon
**  51      <slant>
**  52-53   Day of Full Moon
**  54      <blank>
**  55-56   Hour of Full Moon
**  57      <colon>
**  58-59   Minute of Full Moon
**  60-61   <blank>
**  62-65   Year of Last Quarter
**  66      <slant>
**  67-68   Month of Last Quarter
**  69      <slant>
**  70-71   Day of Last Quarter
**  72      <blank>
**  73-74   Hour of Last Quarter
**  75      <colon>
**  76-77   Minute of Last Quarter
**
** References:
**
** 1.  Meeus, Jean; Astronomical Algorithms, Richmond, Virginia, 1991
**
** 2.  Astronomical Almanac, 1996, Washington, D.C., 1995
**
** 3.  Planetary and Lunar Coordinates 1984-2000, London, 1983
**
*/

#include <stdio.h>
#include <time.h>
#include "moon.h"

static void print_lunation(int lunation, struct tm *event_date);

/*
** define the period of our concern
*/

#define START_LUNATION (-19999)
#define END_LUNATION (19999)

/* offset between lunation numbers and Meeus' formula parameter
   from Astronomical Almanac, and some extrapolation with
   Planetary and Lunar Coordinates 1984-2000 */ 
#define LUNATION_OFFSET 953 

int main(void)
{
  int lun;                     /* lunation number to iterate on */
  int phi;                     /* phase selector, 0 = New Moon,
                                  1 = First Qtr, 2 = Full, 
                                  3 = Last Qtr */
  double JDE;                  /* Julian Ephemeris Day of phase event */
  struct tm event_date[4];     /* storage for the final result */


  for (lun = START_LUNATION; lun <= END_LUNATION; lun++)
  /* for each lunation of concern */
  {
    for (phi = 0; phi <= 3; phi++)
    /* for each phase in the lunation */
    {
      /* generate parameters per Meeus Ch. 47, 45 */
      JDE = moonphasebylunation(lun - LUNATION_OFFSET, phi);
      JDtoDate(JDE, &event_date[phi]);
    }
    print_lunation(lun, event_date);
  }
  return 0;
}


static void print_lunation(int lunation, struct tm *event_date)
/* print the results */
{
  int i;

  printf ("%+5.5d  ", lunation);
  for (i=0; i<=3; i++)
  {
    printf ("%4.4d/%2.2d/%2.2d %2.2d:%2.2d  ",
             event_date[i].tm_year + 1900,
             event_date[i].tm_mon + 1,
             event_date[i].tm_mday,
             event_date[i].tm_hour,
             event_date[i].tm_min);
  }
  if (lunation % 12 == 4) printf("*");
  if (lunation % 12 == -8) printf("*");
  printf("\n");
}
