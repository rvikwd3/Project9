#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include "magick.h"

using namespace Magick;

std::vector<int> getImageDimensions(const Image& image){	//{{{
	std::vector<int> dimensions = {-1, -1};
	

	try{
		dimensions[0] = image.rows();
		dimensions[1] = image.columns();
	}catch (Exception &error_){
		std::cout << "[MAGICK DIMS] Error ocurred:\t" << error_.what() << std::endl;
		return dimensions;
	}

	return dimensions;
}	//}}}

int getImageRows(const Image& image){						//{{{
	int rows;

	try{
		rows = image.rows();
	}catch (Exception &error_){
		std::cout << "[MAGICK ROWS] Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return rows;
}	//}}}

int getImageColumns(const Image& image){					//{{{
	int columns;

	try{
		columns = image.columns();
	}catch (Exception &error_){
		std::cout << "[MAGICK COLS] Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return columns;
}	//}}}

// Returns 2x2x3 rgb vector of each pixel in the image
boost::multi_array< std::array<int, 3>, 2> getImageRgbPixels(const Magick::Image& image){	// {{{

	boost::multi_array< std::array<int, 3>, 2> image_rgb(boost::extents[ image.rows() ][ image.columns() ]);

	for (int i=0; i < image_rgb.shape()[0]; i++){
		for (int j=0; j < image_rgb.shape()[1]; j++){

			image_rgb[i][j][0] = image.pixelColor(j,i).quantumRed();
			image_rgb[i][j][1] = image.pixelColor(j,i).quantumGreen();
			image_rgb[i][j][2] = image.pixelColor(j,i).quantumBlue();

		}
	}

	return image_rgb;
}	// }}}

// Print the dimensions of the passed image as [Rows, Columns] to a file
void printImageDimensions(const Image& image, std::ofstream& outstream){	//{{{
	
	// Call Magick++ RGB Pixel reader
	std::vector<int> dims = getImageDimensions(image);

	// Display Magick++ call results
	outstream << "\nDimensions:\n" << "Rows: " << dims[0] << "\tCols: " << dims[1] << "\n";
}	//}}}

// Print dimensions to stdout
void printImageDimensions(const Image& image){	// {{{
	std::vector<int> dims = getImageDimensions(image);
	std::cout << "\nDimensions:\n" << "Rows: " << dims[0] << "\tCols: " << dims[1] << std::endl;
}	// }}}

// Print the RGB contents of each pixel of the passed image to a file
void printImagePixels(const Image& image, std::ofstream& outstream){	// {{{
	outstream << "\nPixel Colors:" << "\n";

	for(int i=0; i < image.columns(); i++){				// I think we use columns first cause of Linear Algebra?
		for(int j=0; j < image.rows(); j++){

			outstream << "(" << i << ", " << j << std::setw(10) << std::left << ")"
			   	 << "Red: " << std::setw(20) << std::left << image.pixelColor(j,i).quantumRed()
				 << "Green: " << std::setw(20) << std::left << image.pixelColor(j,i).quantumGreen()
				 << "Blue: " << image.pixelColor(j,i).quantumBlue()
				 << std::endl;
		}
	}
}	// }}}

// Print the RGB contents of each pixel to stdout
void printImagePixels(const Image& image){	// {{{
	std::cout << "\nPixel Colors:" << std::endl;

	for(int i=0; i < image.columns(); i++){				// I think we use columns first cause of Linear Algebra?
		for(int j=0; j < image.rows(); j++){

			std::cout << "(" << i << ", " << j << std::setw(10) << std::left << ")"
			   	 << "Red: " << std::setw(20) << std::left << image.pixelColor(j,i).quantumRed()
				 << "Green: " << std::setw(20) << std::left << image.pixelColor(j,i).quantumGreen()
				 << "Blue: " << image.pixelColor(j,i).quantumBlue()
				 << std::endl;
		}
	}
}	// }}}
