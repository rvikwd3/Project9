#include <iostream>
#include <string>
#include <Magick++.h>

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
