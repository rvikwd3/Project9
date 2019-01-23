#ifndef PROJECT9_IMAGE_MATRIX_H
#define PROJECT9_IMAGE_MATRIXH

#include <boost/multi_array.hpp>
#include "convert.h"

class ImageMatrix{
	private:
		//		RGB and HSV matrices
//		boost::multi_array<rgb, 2> rgb_matrix(boost::extents
//		boost::multi_array<hsv, 2> hsv_matrix(
	public:
		ImageMatrix();								//	Initializer
		ImageMatrix(const Magick::Image& image);	//	Image -> Matrix constructor

		rgb  operator() (unsigned row, unsigned col);		//	Retrieve RGB pixel data at (i,j)
		rgb& operator() (unsigned row, unsigned col) const;	//	Use matrix(i, j) as an lvalue
															//		e.g,
															//		matrix(3, 8) = rgb(255, 0, 0);
		hsv  operator() (unsigned row, unsigned col);
		hsv& operator() (unsigned row, unsigned col) const;			

		std::vector<int> getDimensions();			//	Get matrix dimensions

		rgb getRgbAt(unsigned row, unsigned col);	//	Retreive pixel data at (i, j)
		hsv getHsvAt(unsigned row, unsigned col);
		
}
