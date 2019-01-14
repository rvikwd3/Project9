// Utility functions for converting between colorspaces

// Header guard
#ifndef CONVERT_H
#define CONVERT_H

typedef struct rgb {
	double r;
	double g;
	double b;
} rgb;

typedef struct hsv {
	double h;
	double s;
	double v;
} hsv;

namespace Convert{
	hsv rgb2hsv(rgb in);
	rgb hsv2rgb(hsv in);
}

#endif
