//////////////////////////////////////////////////////////////////////////////////
//
//    8888888b.                  d8b                888    .d8888b.
//    888   Y88b                 Y8P                888   d88P  Y88b
//    888    888                                    888   888    888
//    888   d88P888d888 .d88b.  8888 .d88b.  .d8888b888888Y88b. d888
//    8888888P" 888P"  d88""88b "888d8P  Y8bd88P"   888    "Y888P888
//    888       888    888  888  88888888888888     888          888
//    888       888    Y88..88P  888Y8b.    Y88b.   Y88b. Y88b  d88P
//    888       888     "Y88P"   888 "Y8888  "Y8888P "Y888 "Y8888P"
//                               888
//                              d88P
//                            888P"
//
//////////////////////////////////////////////////////////////////////////////////

/*	Project9
 *	C++ Object Detection through Color Connected Components
 *
 *	Ravikiran Kawade
 *
 *	2018-12-30 Start Date
 *	2019-01-06 Read up on Image Segmentation/Quantization
 *		Convert RGB color space to HSV
 *		Use K-means to downsample image (Can we use faster downsampling?) (Is this required?)
 *		Label regions through Connected Component Labelling
 *		Create graph through labels
 *	2019-01-10 Decided to use HSV colorspace instead of L*a*b
 *		Added 'Convert' namespace for utility colorspace conversion functions
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <unistd.h>
#include <list>
#include <exception>

//	Magick++ API
#include <Magick++.h>

//	Boost API
#include <boost/multi_array.hpp>
#include <boost/program_options.hpp>

// Project9 Header files
// Available in the include/ folder
#include "magick.h"
#include "convert.h"
#include "options.h"
#include "imagematrix.h"
#include "constants.h"
#include "segmentation.h"


//using namespace std;		// Bad practice; TODO refactor to not use `using namespace std`

int main (int argc, char** argv) {

    Magick::InitializeMagick(*argv);	// Initialize Magick++ API

    // Boiler plate program argument parsing
    // -------------------------------------------------------------------------------- {{{

    // Check if proper program argument were given
    program_options po;
    try {
        po = boostPrintUsage(argc, argv);
    } catch(std::exception &_error) {
        std::cerr << "[ERROR] Exception occured during parsing program options:" << std::endl;
        std::cerr << _error.what() << "\n" << std::endl;
        boostPrintUsage(constants::HELP_CODE);
        return 1;
    }


    // Check if image filename was provided
    try {
        if ( po.input_file.empty() ) {
			std::cerr << "\nSpecified image is empty!" << std::endl;
			std::cout << "[MAIN]\t" << po.input_file << std::endl;
            boostPrintUsage(constants::HELP_CODE);
            return 1;
        }
    } catch(std::exception &_error) {
        std::cerr << "[ERROR] program_options cannot access input_file!" << std::endl;
        std::cerr << _error.what() << std::endl;
        return 1;
    }


    // Create a Magick++ Image from the given filename
    Magick::Image image(po.input_file);


    // If -d option is given,
    // try displaying the given image
    try {
        if ( po.flag_display ) {
            image.display();
        }
    } catch(Magick::Exception &input_error_) {

		std::cerr << "\nError while trying to display: " << po.input_file << std::endl;
		std::cerr << input_error_.what() << std::endl;
        return 1;
    }

    // If outfile is given, try opening outfile
	std::ofstream outfile_stream ( po.output_file );			// I want to open an outfile stream only if the flag is set
    if ( po.flag_output_file ) {							// This is 99% probably the worst way to do it
        if(!outfile_stream) {
			std::cerr << "\nError while trying to open: " << po.output_file << std::endl;
            return 1;
        }
    }
    // -------------------------------------------------------------------------------- }}}


    // Downscale image to maximum 1000x1000
    // -------------------------------------------------------------------------------- {{{
    std::array<int, 2> resize_dimensions = {{ 200, 200 }};
    image = resizeImage(image, resize_dimensions);
    // -------------------------------------------------------------------------------- }}}

    image.display();			// Display the resized image

    ImageMatrix im(image);		// Initialize an ImageMatrix of the image
	ImageMatrix im2(image);

	double threshold		= 0.5;
	int min_component_size	= 0;

	Segmentor seg(im);

	int no_of_components = 0;
	no_of_components = seg.applySegmentation( threshold, min_component_size );

	std::cout << "[MAIN] No of components: " << no_of_components << std::endl;


    // Print image dimensions
    // -------------------------------------------------------------------------------- {{{
    if ( po.flag_output_file )
        printImageDimensions(image, outfile_stream);
    else
        printImageDimensions(image);

    // Parse image pixel RGB
    if ( po.flag_output_file )
        printImagePixels(image, outfile_stream);
    else
        printImagePixels(image);

    // -------------------------------------------------------------------------------- }}}


    /*	Testing that getImageRgbPixels works fine {{{

    	boost::multi_array< std::array<int, 3>, 2> image_rgb(boost::extents[ getImageRows(image) ][ getImageColumns(image) ]);

    	image_rgb = getImageRgbPixels(image);
    	for ( int i=0; i < getImageRows(image); i++){
    		for ( int j=0; j < getImageColumns(image); j++){

    			std::cout << "Red:\t"   << image_rgb[i][j][0] << std::endl;
    			std::cout << "Green:\t" << image_rgb[i][j][1] << std::endl;
    			std::cout << "Blue:\t"  << image_rgb[i][j][2] << std::endl;
    		 }
    	}
    }}} */

    /*	Testing Convert functions from convert.h {{{

    	rgb		test_rgb;
    	hsv		test_hsv;

    	// We'll convert RGB pixel values to HSV
    	test_rgb.r = 0.5;
    	test_rgb.g = 0.5;
    	test_rgb.b = 0.5;

    	test_hsv.h = 180.0;
    	test_hsv.s = 1.0;
    	test_hsv.v = 1.0;

    	hsv test_rgb_out = Convert::rgb2hsv(test_rgb);
    	rgb test_hsv_out = Convert::hsv2rgb(test_hsv);

    	cout << "H:\t" << test_rgb_out.h << "\tS:\t" << test_rgb_out.s << "\tV:\t" << test_rgb_out.v << endl;
    	cout << "R:\t" << test_hsv_out.r << "\tG:\t" << test_hsv_out.g << "\tB:\t" << test_hsv_out.b << endl;
    }}} */

    /*	Testing ImageMatrix dimensions and pixel data retrieval {{{

    	std::array<int, 2> test_size = im.getDimensions();
    	std::cout << "ImageMatrix sizes: " << test_size[0] << ", " << test_size[1] << std::endl;
    	test_rgb = im.getRgbAt(0,1);
    	test_hsv = im.getHsvAt(0,1);
    	return 0;

    	cout << "\n" << endl;
    }}} */

    return 0;

}
