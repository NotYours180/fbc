/*
 *  libfb - FreeBASIC's runtime library
 *	Copyright (C) 2004-2005 Andre V. T. Vicentini (av1ctor@yahoo.com.br) and others.
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 * time_tmr.c -- win32 timer# function
 *
 * chng: oct/2004 written [v1ctor]
 *
 */

#include <time.h>
#include "fb.h"

#define TIMER_NONE		0
#define TIMER_NORMAL	1
#define TIMER_HIGHRES	2


static int timer = TIMER_NONE;
static double frequency;


/*:::::*/
FBCALL double fb_Timer ( void )
{
	LARGE_INTEGER count;

	if( timer == TIMER_NONE ) {
		if( QueryPerformanceFrequency( &count ) ) {
			frequency = 1.0 / (double)count.QuadPart;
			timer = TIMER_HIGHRES;
		}
		else
			timer = TIMER_NORMAL;
	}

	if( timer == TIMER_NORMAL )
		return (double)GetTickCount( ) * 0.001;
	else {
		QueryPerformanceCounter( &count );
		return (double)count.QuadPart * frequency;
	}
}


