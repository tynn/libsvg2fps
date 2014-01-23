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

#ifndef __svg2fps_animation_h__
#define __svg2fps_animation_h__

#include <stdbool.h>
#include "svg2fps_animation_config.h"

typedef struct svg2fps_animation_handle sah_t;

sah_t * svg2fps_animation_load (char *uri, sac_t *config);

void svg2fps_animation_unload (sah_t *handle);

void svg2fps_animation_set_elapsed_time (double elapsed_time, sah_t *handle);

bool svg2fps_animation_render_as_png (char **buffer, unsigned long *size, sah_t *handle);

#endif // __svg2fps_animation_h__
