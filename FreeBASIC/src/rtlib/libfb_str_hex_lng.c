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
 * str_hex_lng.c -- hex$ routine for long long's
 *
 * chng: apr/2005 written [v1ctor]
 *       jul/2005 rewritten to use consistent case across platforms [DrV] 
 *
 */

#include <malloc.h>
#include <stdlib.h>
#include "fb.h"

static char hex_table[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

/*:::::*/
FBCALL FBSTRING *fb_HEX_l ( unsigned long long num )
{
	FBSTRING 	*dst;
	char		*buf;
	int			i;

	FB_STRLOCK();

	/* alloc temp string */
    dst = fb_hStrAllocTemp( NULL, sizeof( long long ) * 2 );
	if( dst != NULL )
	{
		/* convert */
		buf = dst->data;
		
		if( num == 0ULL )
			*buf++ = '0';
		else
		{
			for( i = 0; i < sizeof( long long )*2; i++, num <<= 4 )
				if( num > 0x0FFFFFFFFFFFFFFFULL )
					break;
	
			for( ; i < sizeof( long long )*2; i++, num <<= 4 )
				if( num > 0x0FFFFFFFFFFFFFFFULL )
					*buf++ = hex_table[(num & 0xF000000000000000ULL) >> 60];
				else
					*buf++ = '0';
		}
		
		/* add null-term */
		*buf = '\0';

        fb_hStrSetLength( dst, buf - dst->data );
	}
	else
		dst = &fb_strNullDesc;

	FB_STRUNLOCK();

	return dst;
}

