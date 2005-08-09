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
 * sys_exepath.c -- exepath$
 *
 * chng: oct/2004 written [v1ctor]
 *
 */

#include <malloc.h>
#include <string.h>
#include "fb.h"

/*:::::*/
FBCALL FBSTRING *fb_ExePath ( void )
{
	FBSTRING 	*dst;
	char		*p;
	char		tmp[MAX_PATH+1];
	int			len;

	p = fb_hGetExePath( tmp, MAX_PATH );

	if( p != NULL )
	{
		FB_STRLOCK();
		
		/* alloc temp string */
        len = strlen( tmp );
        dst = fb_hStrAllocTemp( NULL, len );
		if( dst != NULL )
		{
			fb_hStrCopy( dst->data, tmp, len );
		}
		else
			dst = &fb_strNullDesc;

		FB_STRUNLOCK();
	}
	else
		dst = &fb_strNullDesc;

	return dst;
}
