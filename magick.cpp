#include <iostream>
#include <string>
#include <Magick++.h>

using namespace Magick;

std::vector<int> getImageDimensions(std::string filename){
	std::vector<int> dimensions = {-1, -1};
	

	try{
		Image image(filename);
		dimensions[0] = image.rows();
		dimensions[1] = image.columns();
	}catch (Exception &error_){
		std::cout << "[MAGICK DIMS] Error ocurred:\t" << error_.what() << std::endl;
		return dimensions;
	}

	return dimensions;
}

int getImageRows(std::string filename){
	int rows;

	try{
		Image image(filename);
		rows = image.rows();
	}catch (Exception &error_){
		std::cout << "[MAGICK ROWS] Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return rows;
}

int getImageColumns(std::string filename){
	int columns;

	try{
		Image image(filename);
		columns = image.columns();
	}catch (Exception &error_){
		std::cout << "[MAGICK COLS] Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return columns;
}
