/*
 *	This file is part of libsvg2fps.
 *
 *	Copyright (c) 2014 Christian Schmitz <tynn.dev@gmail.com>
 *
 *	libsvg2fps is free software: you can redistribute it and/or modify
 *	it under the terms of the GNU General Public License as published by
 *	the Free Software Foundation, either version 3 of the License, or
 *	(at your option) any later version.
 *
 *	libsvg2fps is distributed in the hope that it will be useful,
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *	GNU General Public License for more details.
 *
 *	You should have received a copy of the GNU General Public License
 *	along with libsvg2fps. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __svg2fps_error_h__
#define __svg2fps_error_h__

#define NO_MEMORY "No memory"

void svg2fps_error_set_msg (const char *msg);

const char * svg2fps_error_get_msg ( void );

#endif // __svg2fps_error_h__
