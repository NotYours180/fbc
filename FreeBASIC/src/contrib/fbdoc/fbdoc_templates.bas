''  fbdoc - FreeBASIC User's Manual Converter/Generator
''	Copyright (C) 2006 Jeffery R. Marshall (coder[at]execulink.com) and
''  the FreeBASIC development team.
''
''	This program is free software; you can redistribute it and/or modify
''	it under the terms of the GNU General Public License as published by
''	the Free Software Foundation; either version 2 of the License, or
''	(at your option) any later version.
''
''	This program is distributed in the hope that it will be useful,
''	but WITHOUT ANY WARRANTY; without even the implied warranty of
''	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
''	GNU General Public License for more details.
''
''	You should have received a copy of the GNU General Public License
''	along with this program; if not, write to the Free Software
''	Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA.


'' fbdoc_templates - global pseudo class for template loading
''
'' chng: jun/2006 written [coderJeff]
''

#include once "common.bi"
#include once "COptions.bi"

dim shared as COptions ptr temp

'':::::
sub Templates_Create( )
	if( temp <> NULL ) then
		exit sub
	end if
	
	temp = COptions_New( )
	
end sub

'':::::
sub Templates_Destroy( )
	if( temp = NULL ) then
		exit sub
	end if
	
	COptions_Delete( temp )
	temp = NULL
	
end sub

'':::::
function Templates_Set _
	( _
		byval sKey as zstring ptr, _
		byval sValue as zstring ptr _
	) as integer

	Templates_Create()
	if( COptions_Set( temp, sKey, sValue ) ) then
		return TRUE
	end if
	return FALSE

end function

function Templates_LoadFile _
	( _
		byval sKey as zstring ptr, _
		byval sFileName as zstring ptr _
	) as integer

	dim x as string

	x = LoadFileAsString( sFileName )
	
	Templates_Create()
	
	if( COptions_Set( temp, sKey, x ) ) then
		return TRUE
	end if
	
	return FALSE
		
end function

function Templates_Get _
	( _
		byval sKey as zstring ptr _
	) as string

	return COptions_Get( temp, sKey )

end function

