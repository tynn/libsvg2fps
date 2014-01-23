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

#include <webkit/webkit.h>
#include "svg2fps_animation.h"
#include "svg2fps_error.h"

#define JS_PAUSE_ANIMATION "document.documentElement.pauseAnimations&&document.documentElement.pauseAnimations()"
#define JS_SET_CURRENT_TIME_FORMAT "document.documentElement.setCurrentTime&&document.documentElement.setCurrentTime(Number('%f'.replace(',','.')))"
#define JS_SET_CURRENT_TIME_LENGTH 126


struct svg2fps_animation_handle {
	GtkWidget *window;
	WebKitWebView *web_view;
	sac_t *config;
	bool loaded;
	unsigned int width, height;
	double elapsed_time, s, tx, ty;
};


static void _set_zoom_level (int width, int height, sah_t *handle) {
	if (!handle->config || (!handle->config->width && !handle->config->height) || (handle->config->width == width && handle->config->height == height))
		handle->s = 1.0;
	else if (!handle->config->height || (handle->config->width && handle->config->width * height < width * handle->config->height))
		handle->s = (double) handle->config->width / width;
	else
		handle->s = (double) handle->config->height / height;
}


static double _get_translate (int frame, int canvas, sah_t *handle) {
	switch (handle->config->position) {
		case START:
			return 0;
		case END:
			return frame - canvas;
		default:
			return (frame - canvas) / 2.0;
	}
}


static void _set_size (int width, int height, sah_t *handle) {
	handle->width = (int) (handle->s * width);
	if (handle->config && handle->config->width && handle->config->width > handle->width) {
		handle->tx = _get_translate (handle->config->width, handle->width, handle);
		handle->width = handle->config->width;
	}

	handle->height = (int) (handle->s * height);
	if (handle->config && handle->config->height && handle->config->height > handle->height) {
		handle->ty = _get_translate (handle->config->height, handle->height, handle);
		handle->height = handle->config->height;
	}
}


static void _gtk_main_quit (bool loaded, sah_t *handle) {
	gtk_main_quit ();
	handle->loaded = loaded;
}


static void _web_view_load_finished (WebKitWebView *web_view, sah_t *handle) {
	GtkRequisition size;

	webkit_web_view_execute_script (web_view, JS_PAUSE_ANIMATION);
	svg2fps_animation_set_elapsed_time (0, handle);

	gtk_widget_get_preferred_size (GTK_WIDGET(web_view), NULL, &size);
	_set_zoom_level (size.width, size.height, handle);
	/* zooming with small handle->s does not work well; cairo scale does not work at all times but leaves blank images on failure */
	if (handle->s > 1.0)
		webkit_web_view_set_zoom_level (web_view, (gfloat) handle->s);
	_set_size (size.width, size.height, handle);

	_gtk_main_quit (true, handle);
}


static void on_web_view_notify_load_status (WebKitWebView *web_view, GParamSpec *param_spec, sah_t *handle) {
	switch (webkit_web_view_get_load_status (web_view)) {
		case WEBKIT_LOAD_FINISHED:
			_web_view_load_finished (web_view, handle);
			break;
		case WEBKIT_LOAD_FAILED:
			_gtk_main_quit (false, handle);
			break;
		default:
			break;
	}
}


static void _create_window (sah_t *handle) {
	GdkVisual *visual;

	handle->window = gtk_offscreen_window_new ();
	visual = gdk_screen_get_rgba_visual (gtk_widget_get_screen (handle->window));
	if (visual)
		gtk_widget_set_visual (handle->window, visual);
}


static void _create_web_view (sah_t *handle) {
	WebKitWebSettings *web_settings;

	handle->web_view = WEBKIT_WEB_VIEW(webkit_web_view_new ());
	webkit_web_view_set_full_content_zoom (handle->web_view, true);
	webkit_web_view_set_transparent (handle->web_view, true);
	g_signal_connect (G_OBJECT(handle->web_view), "notify::load-status", G_CALLBACK(on_web_view_notify_load_status), handle);

	web_settings = webkit_web_view_get_settings (handle->web_view);
	g_object_set (G_OBJECT(web_settings), "enable-plugins", false, NULL);
	g_object_set (G_OBJECT(web_settings), "enable-java-applet", false, NULL);
}


static void _show_all (sah_t *handle) {
	gtk_container_add (GTK_CONTAINER(handle->window), GTK_WIDGET(handle->web_view));
	gtk_widget_show_all (handle->window);
}


static void _gtk_main () {
	while (gtk_events_pending ())
		gtk_main_iteration ();
}


static bool _after_gtk_main_quit (sah_t *handle) {
	if (handle->loaded) {
		_gtk_main ();
		gtk_main_iteration ();
		return true;
	} else {
		svg2fps_animation_unload (handle);
		svg2fps_error_set_msg ("Loading document failed");
		return false;
	}
}


sah_t * svg2fps_animation_load (char *uri, sac_t *config) {
	sah_t *handle;

	handle = g_malloc (sizeof(sah_t));

	if (handle) {
		handle->config = config;
		handle->loaded = false;

		gtk_init (0, NULL);
		_create_window (handle);
		_create_web_view (handle);
		_show_all (handle);

		webkit_web_view_load_uri (handle->web_view, uri);
		gtk_main ();

		if (_after_gtk_main_quit (handle))
			return handle;
	} else {
		svg2fps_error_set_msg (NO_MEMORY);
	}

	return NULL;
}


void svg2fps_animation_unload (sah_t *handle) {
	if (handle) {
		if (handle->window)
			gtk_widget_destroy (handle->window);
		g_free (handle);
	}
}


void svg2fps_animation_set_elapsed_time (double elapsed_time, sah_t *handle) {
	static char script [JS_SET_CURRENT_TIME_LENGTH];

	if (handle) {
		if (handle->config)
			elapsed_time += handle->config->time_offset;

		if (handle->loaded && handle->elapsed_time != elapsed_time) {
			sprintf (script, JS_SET_CURRENT_TIME_FORMAT, elapsed_time);
			webkit_web_view_execute_script (handle->web_view, script);
			_gtk_main ();
			handle->elapsed_time = elapsed_time;
		}
	}
}


bool svg2fps_animation_render_as_png (char **buffer, unsigned long *size, sah_t *handle) {
	static char error[34];
	cairo_surface_t *surface;
	cairo_t *cr;
	cairo_status_t status;
	GdkPixbuf *pixbuf;
	sac_rgba *color [2] = { NULL, NULL };

	if (handle && handle->loaded) {
		surface = cairo_image_surface_create (CAIRO_FORMAT_ARGB32, handle->width, handle->height);
		status = cairo_surface_status (surface);
		if (status != CAIRO_STATUS_SUCCESS) {
			sprintf (error, "Cairo surface status: %d", status);
			svg2fps_error_set_msg (error);
			return false;
		}

		cr = cairo_create (surface);
		status = cairo_status (cr);
		if (status != CAIRO_STATUS_SUCCESS) {
			sprintf (error, "Cairo status: %d", status);
			svg2fps_error_set_msg (error);
			return false;
		}

		cairo_set_operator (cr, CAIRO_OPERATOR_SOURCE);

		if (handle->config) {
			color [0] = handle->config->border;
			color [1] = handle->config->background;
		}

		if (color [0]) {
			cairo_set_source_rgba (cr, color[0]->r, color[0]->g, color[0]->b, color[0]->a);
			cairo_paint (cr);
		}

		cairo_translate (cr, handle->tx, handle->ty);

		/* this could be buggy with some double values for handle->s */
		if (handle->s < 1.0)
			cairo_scale (cr, handle->s, handle->s);

		gtk_widget_draw (GTK_WIDGET(handle->web_view), cr);

		if (color [1]) { 
			cairo_set_operator (cr, CAIRO_OPERATOR_DEST_OVER);
			cairo_set_source_rgba (cr, color[1]->r, color[1]->g, color[1]->b, color[1]->a);
			cairo_paint (cr);
		}

		pixbuf = gdk_pixbuf_get_from_surface (surface, 0, 0, handle->width, handle->height);

		cairo_destroy (cr);
		cairo_surface_destroy (surface);

		if (pixbuf) {
			gdk_pixbuf_save_to_buffer (pixbuf, (gchar **) buffer, (gsize *) size, "png", NULL, NULL);
			g_object_unref (pixbuf);
			return true;
		} else {
			svg2fps_error_set_msg ("Creating GdkPixbuf failed");
		}
	} else {
		svg2fps_error_set_msg ("Svg data not present");
	}

	return false;
}


