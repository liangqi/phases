/*
** jd.h
**
** Headers and function defs for julian date routines
**
*/

#if !defined __JD_H
#define __JD_H

#include <time.h>

extern time_t JDtoDate(double jd, struct tm *event_date);  /* jd.c     */
extern double DatetoJD(struct tm *event_date);  /* jd.c */

#endif /* __JD_H */
