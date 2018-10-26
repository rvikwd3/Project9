#include <iostream>

// Try including the libraries
#include <IL/il.h>
#include <IL/ilu.h>
#include <IL/ilut.h>

int main(){
	// Include IL
	ilInit();
	std::cout << "Initialized IL" << std::endl;;

	// Include ILU
	//iluInit();

	// Include ILUT with OpenGL API support
	//ilutRenderer(ILUT_OPENGL);
	
	// Generate an Image Name
	ILuint image_name;
	ilGenImages(1, &image_name);

	// Bind image_name
	ilBindImage(image_name);
	std::cout << "Bound image_name" << std::endl;;

	// Load the 2x2 image
	char filename[] = "2x2.png";
	ilLoadImage(filename);
	std::cout << "Loaded 2x2.png" << std::endl;;

	// Save the image under a different name
	ilSaveImage("convert.png");
	std::cout << "Saved convert.png" << std::endl;;

	// Delete the image
	ilDeleteImage(image_name);

	std::cout << "" << std::endl;;

	return 0;
}
