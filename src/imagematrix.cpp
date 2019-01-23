#include "imagematrix.h"

Imagematrix::ImageMatrix(){
	// Initialize RGB and HSV matrices
}

ImageMatrix::ImageMatrix(const Magick::Image& image){
	// Get image dimensions
	// Initialize RGB & HSV matrices to dimension size
	
	// Copy RGB data to RGB matrix
	// Convert RGB data to HSV matrix
}

std::vector<int> ImageMatrix::getDimensions(){
	// return matrix size
}

rgb ImageMatrix::getRgbAt(unsigned row, unsigned col){
	// return this(row, col);
}

hsv ImageMatrix::getHsvAt(unsigned row, unsigned col){
	// return this(row, col);
}
