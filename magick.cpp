#include <iostream>
#include <string>
#include <Magick++.h>

using namespace Magick;

std::vector<int> getImageDimensions(std::string filename){
	std::vector<int> dimensions = {-1, -1};
	
	Image image(filename);

	try{
		dimensions[0] = image.rows();
		dimensions[1] = image.columns();
	}catch (Exception &error_){
		std::cout << "Error ocurred:\t" << error_.what() << std::endl;
		return dimensions;
	}

	return dimensions;
}

int getImageRows(std::string filename){
	Image image(filename);
	int rows;

	try{
		rows = image.rows();
	}catch (Exception &error_){
		std::cout << "Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return rows;
}

int getImageColumns(std::string filename){
	Image image(filename);
	int columns;

	try{
		columns = image.columns();
	}catch (Exception &error_){
		std::cout << "Error ocurred:\t" << error_.what() << std::endl;
		return 1;
	}

	return columns;
}
