libsvg2fps
==========

*libsvg2fps* is a library to render an SVG animation as PNG frames.

The interface for *libsvg2fps* to handle requests for frames is defined in [svg2fps.h](svg2fps.h).  
The SVG animation handling itself is defined in [svg2fps_animation.h](svg2fps_animation.h).

The *GTK+* implementation is the sole backend for the time being.


Installation
------------

Create *libsvg2fps* with

	 ./configure && make

and install with

	 sudo make install

If the configure script does not exist, run

	 autoreconf -fi

first.

