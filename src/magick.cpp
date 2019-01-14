#include <iostream>
#include <iomanip>
#include <string>
#include <Magick++.h>
#include <fstream>

using namespace Magick;

std::vector<int> getImageDimensions(Image image){
	std::vector<int> dimensions = {-1, -1};
	

	try{
		dimensions[0] = image.rows();
		dimensions[1] = image.columns();
	}catch (Exception &error_){
		std::cout << "[MAGICK DIMS] Error ocurred:\t" << error_.what() << std::endl;
		return dimensions;
	}

	return dimensions;
}

int getImageRows(Image image){
	int rows;

	try{
		rows = image.rows();
	}catch (Exception &error_){
		std::cout << "[MAGICK ROWS] Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return rows;
}

int getImageColumns(Image image){
	int columns;

	try{
		columns = image.columns();
	}catch (Exception &error_){
		std::cout << "[MAGICK COLS] Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return columns;
}

void printImageDimensions(Magick::Image image){
	
	// Call Magick++ RGB Pixel reader
	std::vector<int> dims = getImageDimensions(image);

	// Display Magick++ call results
	std::cout << "Dimensions:\n" << "Rows: " << dims[0] << "\tCols: " << dims[1] << std::endl;
}

void printImagePixels(Magick::Image image){
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
}
