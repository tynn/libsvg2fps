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

#include <stdlib.h>
#include "svg2fps.h"
#include "svg2fps_animation.h"
#include "svg2fps_error.h"

#define FPS_MAX 120


struct svg2fps_animation_data {
	sah_t *handle;
	char *uri;
	int fps;
};


sad_t * svg2fps_load_document (char *uri, int fps, sac_t *config) {
	sad_t *data;

	if (fps < 1 || fps > FPS_MAX)
		return NULL;

	data = malloc (sizeof(sad_t));

	if (data) {
		data->uri = uri;
		data->fps = fps;
		data->handle = svg2fps_animation_load (uri, config);

		if (data->handle)
			return data;

		free (data);
	} else {
		svg2fps_error_set_msg (NO_MEMORY);
	}

	return NULL;
}


void svg2fps_unload_document (sad_t *data) {
	if (data) {
		if (data->handle)
			svg2fps_animation_unload (data->handle);
		free (data);
	}
}


bool svg2fps_render_frame_as_png (int frame, char **buffer, unsigned long *size, sad_t *data) {
	if (!data || !data->handle)
		return false;

	svg2fps_animation_set_elapsed_time ((double) frame / data->fps, data->handle);

	return svg2fps_animation_render_as_png (buffer, size, data->handle);
}


