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
 * io_gety.c -- GetY function for Windows
 *
 * chng: jan/2005 written [v1ctor]
 *
 */

#include "fb.h"

/*:::::*/
int fb_ConsoleGetRawY( void )
{
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo( fb_out_handle, &info );
    return info.dwCursorPosition.Y + 1;
}

/*:::::*/
int fb_ConsoleGetY( void )
{
#if FB_CON_BOUNDS==1 || FB_CON_BOUNDS==2
    int add_y;
    fb_ConsoleGetWindow( NULL, &add_y, NULL, NULL );
    return fb_ConsoleGetRawY() - add_y + 1;
#else
    return fb_ConsoleGetRawY();
#endif
}

