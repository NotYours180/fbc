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
 * str_rtrim.c -- rtrim$ function
 *
 * chng: oct/2004 written [v1ctor]
 *
 */

#include <malloc.h>
#include "fb.h"


/*:::::*/
FBCALL FBSTRING *fb_RTRIM ( FBSTRING *src )
{
	FBSTRING 	*dst;
	int 		len;
	char		*p;

	if( src == NULL )
		return &fb_strNullDesc;

   	FB_STRLOCK();

	len = 0;
	if( src->data != NULL )
	{
		len = FB_STRSIZE( src );
		if( len > 0 )
		{
			p = fb_hStrSkipCharRev( src->data, len, 32 );
			len = (int)(p - src->data) + 1;
		}
	}

	if( len > 0 )
	{
		/* alloc temp string */
        dst = fb_hStrAllocTemp( NULL, len );
		if( dst != NULL )
		{
			/* simple copy */
			fb_hStrCopy( dst->data, src->data, len );
		}
		else
			dst = &fb_strNullDesc;
    }
	else
		dst = &fb_strNullDesc;

	/* del if temp */
	fb_hStrDelTemp( src );

   	FB_STRUNLOCK();

	return dst;
}

