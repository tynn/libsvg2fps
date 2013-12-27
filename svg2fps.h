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

#ifndef __svg2fps_h__
#define __svg2fps_h__

#include <stdbool.h>
#include "svg2fps_animation_config.h"

typedef struct svg2fps_animation_data sad_t;

sad_t * svg2fps_load_document (char *uri, int fps, sac_t *config);

void svg2fps_unload_document (sad_t *data);

bool svg2fps_render_frame_as_png (int frame, char **buffer, unsigned long *size, sad_t *data);

#endif // __svg2fps_h__
