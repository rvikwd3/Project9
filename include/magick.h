// Magick++ API Usage for Project9

// Header Guard
#ifndef MAGICK_H
#define MAGICK_H

#include <Magick++.h>

int getImageColumns(const Magick::Image& image);
int getImageRows(const Magick::Image& image);
std::vector<int> getImageDimensions(const Magick::Image& image);

void printImageDimensions(const Magick::Image& image, std::ofstream& outstream);
void printImageDimensions(const Magick::Image& image);
void printImagePixels(const Magick::Image& image, std::ofstream& outstream);
void printImagePixels(const Magick::Image& image);

#endif
