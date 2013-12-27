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

AC_INIT([libsvg2fps], [0.1])
AC_CONFIG_AUX_DIR([config])
AC_CONFIG_MACRO_DIR([m4])

AM_INIT_AUTOMAKE([foreign])
LT_INIT([disable-static])

AC_ARG_VAR([engine], [implementation used to render the SVG files, defaults to 'gtk'])
AS_CASE([$engine], [engine=gtk AC_SUBST([VERSION_INFO], [0:0:0]) PKG_CHECK_MODULES([libwebkitgtk], [webkitgtk-3.0])])
AM_CONDITIONAL([GTK], [test "$engine" = gtk])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT

