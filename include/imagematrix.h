#ifndef PROJECT9_IMAGE_MATRIX_H
#define PROJECT9_IMAGE_MATRIX_H

#include <Magick++.h>
#include <boost/multi_array.hpp>
#include "convert.h"


class ImageMatrix {
private:
    //		RGB and HSV matrices
    boost::multi_array<rgb, 2> rgb_matrix;
    boost::multi_array<hsv, 2> hsv_matrix;

//		long unsigned int width = 0;
//		long unsigned int height = 0;

public:
    // Constructors
    ImageMatrix();								//	Initializer
    ImageMatrix(const Magick::Image& image);	//	Image -> Matrix constructor

    // Pixel data retreival
    // 		Is operator() overloading absolutely necessary?

    //template <typename T>
    //	T operator() (unsigned row, unsigned col);
    //rgb  operator() (unsigned row, unsigned col, int matrix_specifier);
    //rgb& operator() (unsigned row, unsigned col, int matrix_specifier) const;
    //	Retrieve RGB pixel data at (i,j)
    //	Use matrix(i, j) as an lvalue
    //		e.g,
    //		matrix(3, 8) = rgb(255, 0, 0);

    //hsv  operator() (unsigned row, unsigned col);
    //hsv& operator() (unsigned row, unsigned col) const;

    rgb getRgbAt(unsigned row, unsigned col);	//	Retreive pixel data at (i, j)
    hsv getHsvAt(unsigned row, unsigned col);

    //	Get matrix dimensions
    std::array<int, 2> getDimensions();

};

/*
 * Trying out templated return types for operators

template <typename T>
T ImageMatrix::operator() (unsigned row, unsigned col){

	T retval;
	fprintf(stderr, "[ERROR] Please specify RGB or HSV for ImageMatrix::Operator(%d, %d)", row, col);

	return retval;
}

template <>
rgb ImageMatrix::operator() <rgb> (unsigned row, unsigned col){

	rgb retval;
	std::array<int, 2> matrix_size = this->getDimensions();

	if ( (row >= matrix_size[0]) || (col >= matrix_size[1]) ){
		fprintf(stderr, "[ERROR] Operator(%d, %d) is trying to access elements outside of the image matrix", row, col);
		return retval;
	}

	// get rgb values from imagematrix
	retval.r = rgb_matrix[row][col].r;
	retval.g = rgb_matrix[row][col].g;
	retval.b = rgb_matrix[row][col].b;

	printf("[Operator(%d, %d)] \tR: %9.2f\tG: %9.2f\tB: %9.2f\n", row, col, retval.r, retval.g, retval.b);

	return retval;

}

template <>
hsv ImageMatrix::operator() <hsv> (unsigned row, unsigned col){

*/
#endif
