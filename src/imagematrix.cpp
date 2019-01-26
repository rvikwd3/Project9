#include "imagematrix.h"
#include "magick.h"

Imagematrix::ImageMatrix(){
	std::cout << "[IMAGE MATRIX] Please specify the image size to ImageMatrix" << std::endl;
	// Initialize RGB and HSV matrices
}

ImageMatrix::ImageMatrix(const Magick::Image& image){
	// Get image dimensions
	std::vector<int> dims = image.getDimensions(image);
	
	// Initialize RGB & HSV matrices to dimension size
	rgb_matrix A(boost::extents[ dims[0] ][ dims[1] ]);
	hsv_matrix A(boost::extents[ dims[0] ][ dims[1] ]);

	// Copy RGB data to RGB matrix
	for ( size_t i = 0; i < rgb_matrix.shape()[0]; i++){
		for (size_t j = 0; j < rgb_matrix.shape()[1]; j++){
		}
	}
			
	
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
