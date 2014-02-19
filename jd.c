/*
** jd.c:
** 1996/02/11
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
** convert a Julian Day number to a struct tm
**
** Parameter:
**   double jd:  Julian day number with fraction of day
**
** Returns:
**   struct tm *event_date:  Date-time group holding year, month, day, hour,
**                and minute of the event
*/

#include <time.h>
#include "jd.h"

extern time_t JDtoDate(double jd, struct tm *event_date)
/* convert a Julian Date to a date-time group */
{
  long a, a1, z, b, c, d, e;
  double f, day;

  jd += 0.5;
  z = (long) jd;
  f = jd - z;

  if (z < 2299161)
  {
    a = z;
  }
  else
  {
    a1 = (long) ((z - 1867216.25) / 36524.25);
    a = z + 1 + a1 - (long)(a1 / 4);
  }

  b = a + 1524;
  c = (long)((b - 122.1) / 365.25);
  d = (long)(365.25 * c);
  e = (long)((b - d)/30.6001);

  day = b - d - (long)(30.6001 * e) + f;

  if (e < 14)
  {
    event_date->tm_mon = (e - 1) - 1;
  }
  else
  {
    event_date->tm_mon = (e - 13) - 1;
  }

  if (event_date->tm_mon > (2 - 1))
  {
    event_date->tm_year = c - 4716 - 1900;
  }
  else
  {
    event_date->tm_year = c - 4715 - 1900;
  }
  event_date->tm_mday = (int)day;
  day -= event_date->tm_mday;
  day *= 24;
  event_date->tm_hour = (int)day;
  day -= event_date->tm_hour;
  day *= 60;
  event_date->tm_min = (int)day;
  day -= event_date->tm_min;
  day *= 60;
  event_date->tm_sec = (int)day;

  event_date->tm_isdst = -1;

  return mktime(event_date);
}

extern double DatetoJD(struct tm *event_date)
/* convert a date-time group to a JD with fraction */
{
  int y, m;
  double d;
  int a, b;
  double jd;

  y = event_date->tm_year + 1900;
  m = event_date->tm_mon + 1;
  d = (double)(event_date->tm_mday) + (event_date->tm_hour / 24.0) 
    + (event_date->tm_min / 1440.0) + (event_date->tm_sec / 86400.0);

  if (m == 1 || m == 2)
  {
    y--;
    m += 12;
  }

  a = (int)(y / 100);
  b = 2 - a + (int)(a / 4);

  if (y < 1583)
    if ((y < 1582) || (m < 10) || ((m == 10) && (d <= 15)))
      b = 0;

  jd = (long)(365.25 * (y + 4716)) + (long)(30.6001 * (m+1))
     + d + b - 1524.5;
  
  return jd;
}

