/*
 *	This file is part of libsvg2fps.
 *	
 *	Copyright (c) 2013 Christian Schmitz <tynn.dev@gmail.com>
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

#ifndef __svg2fps_animation_config_h__
#define __svg2fps_animation_config_h__

typedef enum svg2fps_animation_config_position { CENTER, START, END } sac_pos;

typedef struct svg2fps_animation_config_rgba {
	double r, g, b, a;
} sac_rgba;

typedef struct svg2fps_animation_config {
	unsigned int width, height;
	double time_offset;
	sac_pos position;
	sac_rgba *background, *border;
} sac_t;

#endif // __svg2fps_animation_config_h__
