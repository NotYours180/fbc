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
 * io_width.c -- width (console, no gfx) for Linux
 *
 * chng: jan/2005 written [lillo]
 *
 */

#include "fb.h"
#include "fb_linux.h"

/*:::::*/
int fb_ConsoleWidth( int cols, int rows )
{
	char buffer[16];
	int cur = (fb_con.inited? fb_con.w | (fb_con.h << 16) : 80 | (25 << 16));
	
	if ((fb_con.inited == INIT_XTERM) || (fb_con.inited == INIT_ETERM)) {
		if (cols <= 0)
			cols = fb_con.w;
		if (rows <= 0)
			rows = fb_con.h;
		sprintf(buffer, "\e[8;%d;%dt", rows, cols);
		fputs(buffer, fb_con.f_out);
		fb_con.resized = TRUE;
		fb_hResize();
	}

	return cur;
}
