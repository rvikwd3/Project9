// Magick++ API Usage for Project9

// Header Guard
#ifndef MAGICK_H
#define MAGICK_H

#include <Magick++.h>

int getImageColumns(Magick::Image image);
int getImageRows(Magick::Image image);
std::vector<int> getImageDimensions(Magick::Image image);

void printImageDimensions(Magick::Image image);
void printImagePixels(Magick::Image image);

#endif
