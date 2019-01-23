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
 *		Convert RGB color space to La*b*
 *		Use K-means to downsample image (Can we use faster downsampling?) (Is this required?)
 *		Label regions through Connected Component Labelling
 *		Create graph through labels
 *	2019-01-10 Decided to use HSV colorspace instead
 *		Added 'Convert' namespace for utility colorspace conversion functions
*/

#include <fstream>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <unistd.h>
#include <list>

#include <Magick++.h>		//	Magick++ API

// Project9 Header files
// Available in the include/ folder
#include "magick.h"
#include "convert.h"
#include "options.h"


using namespace std;		// Bad practice; TODO refactor to not use `using namespace std`

int main (int argc, char** argv){
	
	program_options po = boostPrintUsage(argc, argv);
	cout << "[MAIN]\t" << po.input_file << endl;

	Magick::InitializeMagick(*argv);	// Initialize Magick++ API

	// Check if image filename was provided
	if ( po.input_file.empty() ){
		cerr << "\nImage filename not provided!" << endl;
		return 1;
	}

	try{
		Magick::Image image(po.input_file);

		if ( po.flag_display ) {image.display();} 
	}catch(Magick::Exception &input_error_){
		
		cerr << "\nError while trying to open: " << po.input_file << endl;
		cerr << input_error_.what() << endl;
		return 1;
	}

	// If outfile is given, try opening outfile
	ofstream outfile_stream ( po.output_file );			// I want to open an outfile stream only if the flag is set
	if ( po.flag_output_file ){							// This is 99% probably the worst way to do it
		if(!outfile_stream){
			cerr << "\nError while trying to open: " << po.output_file << endl;
			return 1;
		}
	}

	// Parse image dimensions
	if ( po.flag_output_file )
		printImageDimensions(po.input_file, outfile_stream);
	else
		printImageDimensions(po.input_file);
	
	// Parse image pixel RGB
	if ( po.flag_output_file )
		printImagePixels(po.input_file, outfile_stream);
	else
		printImagePixels(po.input_file);


	// We'll convert RGB pixel values to HSV
	rgb		test_rgb;
	hsv		test_hsv;
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

	return 0;

	cout << "\n" << endl;

}
