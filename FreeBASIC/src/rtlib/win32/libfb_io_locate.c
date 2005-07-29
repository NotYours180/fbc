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
 * io_locate.c -- locate (console, no gfx) function for Windows
 *
 * chng: jan/2005 written [v1ctor]
 *
 */

#include "fb.h"

int fb_ConsoleGetRawX( void );
int fb_ConsoleGetRawY( void );

/*:::::*/
int fb_ConsoleLocateEx( int row, int col, int cursor, int do_xyadjust )
{
	COORD c;
    CONSOLE_CURSOR_INFO info;
    int ret_val;

    if( col > 0 ) {
  		c.X = col - 1;
    } else {
        if( do_xyadjust ) {
            c.X = fb_ConsoleGetX() - 1;
        } else {
            c.X = fb_ConsoleGetRawX() - 1;
        }
    }

    if( row > 0 ) {
  		c.Y = row - 1;
    } else {
        if( do_xyadjust ) {
            c.Y = fb_ConsoleGetY() - 1;
        } else {
            c.Y = fb_ConsoleGetRawY() - 1;
        }
    }

	GetConsoleCursorInfo( fb_out_handle, &info );

    ret_val =
        ((c.X + 1) & 0xFF) | (((c.Y + 1) & 0xFF) << 8) | (info.bVisible ? 0x10000 : 0);

#if (FB_CON_BOUNDS==1) || (FB_CON_BOUNDS==2)
    if( do_xyadjust ) {
        int add_x, add_y;
        fb_ConsoleGetWindow( &add_x, &add_y, NULL, NULL );
#if FB_CON_BOUNDS==1
        c.X += add_x - 1;
#endif
        c.Y += add_y - 1;
    }
#endif

  	if( cursor >= 0 ) {
  		info.bVisible = ( cursor ? TRUE : FALSE );
  		SetConsoleCursorInfo( fb_out_handle, &info );
  	}

  	SetConsoleCursorPosition( fb_out_handle, c );

	return ret_val;
}

/*:::::*/
int fb_ConsoleLocateRaw( int row, int col, int cursor )
{
	return fb_ConsoleLocateEx( row, col, cursor, FALSE );
}

/*:::::*/
int fb_ConsoleLocate( int row, int col, int cursor )
{
	return fb_ConsoleLocateEx( row, col, cursor, TRUE );
}

