/* Color space conversion utility funcitons
 * RGB to HSV
 * HSV to RGB
 *
 * Conversion formulas are given at https://stackoverflow.com/questions/3018313/algorithm-to-convert-rgb-to-hsv-and-hsv-to-rgb-in-range-0-255-for-both
*/

#include "convert.h"
#include <iostream>

namespace Convert {
// --------------------------------------------------------------------------------
// Only accepts values from 0.0 to 1.0
// No parameter input checking!
// 	TODO:	Test input in range 0.0-1.0
hsv rgb2hsv(rgb in) {	// {{{
    hsv 	out;
    double	min, max, delta;

    min = in.r < in.g ? in.r : in.g;
    min = min  < in.b ? min  : in.b;

    max = in.r > in.g ? in.r : in.g;
    max = max  > in.b ? max  : in.b;

    out.v = max;
    delta = max - min;

    if ( delta < 0.00001 ) {		// grayscale rgb color
        out.s = 0;
        out.h = 0;
        return out;
    }

    if ( max > 0.0 ) {
        out.s = ( delta / max );
    } else {					// rgb is black
        out.s = 0.0;
        out.h = 0.0;

        //std::cerr << "Hue is undefined" << std::endl;
        //		Was printing too many Hue is undefined

        return out;
    }

    if ( in.r >= max )
        out.h = ( in.g - in.b ) / delta;		// between yellow & magenta
    else if ( in.g >= max )
        out.h = 2.0 + ( in.b - in.r ) / delta;	// between cyan & yellow
    else
        out.h = 4.0 + ( in.r - in.g ) / delta;	// between magenta & cyan


    out.h *= 60;				// convert to degrees

    if ( out.h < 0.0 )
        out.h += 360;


    return out;
}	// }}}
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
// Only accepts values from 0.0 to 1.0
// No parameter input checking!
// 	TODO:	Test input in range 0.0-1.0
rgb hsv2rgb(hsv in) {	// {{{

    rgb		out;
    double	hh, p, q, t, ff;
    long	i;

    if ( in.s <= 0.0 ) {
        out.r = in.v;
        out.g = in.v;
        out.b = in.v;

        return out;
    }

    hh = in.h;

    if ( hh >= 360.0)
        hh = 0.0;

    hh /= 60.0;

    i = (long) hh;

    ff = hh - i;

    p = in.v * ( 1.0 - in.s );
    q = in.v * ( 1.0 - ( in.s * ff ));
    t = in.v * ( 1.0 - ( in.s * ( 1.0 - ff )));

    switch (i) {
    case 0:
        out.r = in.v;
        out.g = t;
        out.b = p;
        break;

    case 1:
        out.r = q;
        out.g = in.v;
        out.b = p;
        break;

    case 2:
        out.r = p;
        out.g = in.v;
        out.b = t;
        break;

    case 3:
        out.r = p;
        out.g = q;
        out.b = in.v;
        break;

    case 4:
        out.r = t;
        out.g = p;
        out.b = in.v;
        break;

    case 5:
    default:
        out.r = in.v;
        out.g = p;
        out.b = q;
        break;
    }

    return out;
}	// }}]

}
