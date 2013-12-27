#	This file is part of libsvg2fps.
#	
#	Copyright (c) 2013 Christian Schmitz <tynn.dev@gmail.com>
#
#	libsvg2fps is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	libsvg2fps is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with libsvg2fps. If not, see <http://www.gnu.org/licenses/>.

ACLOCAL_AMFLAGS = -I m4

pkginclude_HEADERS = svg2fps.h svg2fps_animation.h svg2fps_animation_config.h

lib_LTLIBRARIES = libsvg2fps.la
libsvg2fps_la_SOURCES = svg2fps.c
libsvg2fps_la_LDFLAGS = -release $(engine) -version-info $(VERSION_INFO)

if GTK
libsvg2fps_la_SOURCES += svg2fps_animation_gtk.c
libsvg2fps_la_CFLAGS = $(libwebkitgtk_CFLAGS)
libsvg2fps_la_LIBADD = $(libwebkitgtk_LIBS)
endif

dist_doc_DATA = README.md LICENSE AUTHORS

