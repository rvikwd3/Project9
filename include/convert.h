// Utility functions for converting between colorspaces

// Header guard
#ifndef CONVERT_H
#define CONVERT_H

typedef struct rgb {
    double r;
    double g;
    double b;

    // Initialization list constructor
    rgb() 								: r(-1.0), g(-1.0), b(-1.0) {}
    rgb(int r, int g, int b) 			: r(r), g(g), b(b) {}
    rgb(double r, double g, double b) 	: r(r), g(g), b(b) {}
} rgb;

typedef struct hsv {
    double h;
    double s;
    double v;

    // Initialization list constructor
    hsv() 								: h(-1.0), s(-1.0), v(-1.0) {}
    hsv(int h, int s, int v) 			: h(h), s(s), v(v) {}
    hsv(double h, double s, double v) 	: h(h), s(s), v(v) {}
} hsv;

namespace Convert {

hsv rgb2hsv(rgb in);
rgb hsv2rgb(hsv in);
}

#endif
