// Magick++ API Usage for Project9

// Header Guard
#ifndef MAGICK_H
#define MAGICK_H

#include <Magick++.h>
#include <boost/multi_array.hpp>

int getImageColumns(const Magick::Image& image);
int getImageRows(const Magick::Image& image);
std::vector<int> getImageDimensions(const Magick::Image& image);

boost::multi_array< std::array<int, 3>, 2> getImageRgbPixels(const Magick::Image& image);

void printImageDimensions(const Magick::Image& image, std::ofstream& outstream);
void printImageDimensions(const Magick::Image& image);
void printImagePixels(const Magick::Image& image, std::ofstream& outstream);
void printImagePixels(const Magick::Image& image);

#endif
