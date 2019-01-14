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
#include <Magick++.h>
#include "magick.h"
#include "convert.h"

using namespace std;

void printUsage(void);

int main (int argc, char** argv){

	
	Magick::InitializeMagick(*argv);	// Initialize Magick++ API

	// Using getopt to parse input arguments
	// -------------------------------------
	int opt;
	bool image_input_flag 	= false;			// Program argument flags
	bool outfile_flag 		= false;
	string input 			= "";				// Program argument strings
	string outfile 			= "";

	if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ){ // Retrieve the non-option argument
		cerr << "No arguments given!\n" << endl;
		printUsage();

		return -1;
	}

	// Display arguments passed to shell
	// ---------------------------------
	for(int i=0; i<argc; i++){
		cerr << "Argument " << i << ":\t" << argv[i] << endl;
	}

	opterr = 0;	// Turn off getopt error messages (default case)

	while ( (opt = getopt(argc, argv, "f:o:")) != -1) {				// Retreive options
		switch(opt){
			case 'f':
				if(optarg) input = optarg;
				cerr << "[GETOPT] Input = " << input << endl;		// Store image filename in input
				image_input_flag	= true;							// Set input flag
				break;

			case 'o':
				if(optarg) outfile = optarg;
				cerr << "[GETOPT] Outfile = " << outfile << endl;	// Store outfile filename in outfile
				outfile_flag 		= true;							// Set outfile flag
				break;
				
			case '?':
				cerr << "Unknown option: " << char(optopt) << endl;
				exit(1);
				break;
			}
	}

	// Check if image filename was provided
	if ( ! image_input_flag ){
		cerr << "\nImage filename not provided!" << endl;
		printUsage();
	}

	try{
		Magick::Image image(input);
	}catch(Magick::Exception &input_error_){
		
		cerr << "\nError while trying to open: " << input << endl;
		cerr << input_error_.what() << endl;
		return 1;
	}

	// Try opening outfile
	ofstream outfile_stream ( outfile );
	if(!outfile_stream){
		cerr << "\nError while trying to open: " << outfile << endl;
		return 1;
	}

	// Parse image dimensions
	printImageDimensions(input, outfile_stream);
	
	// Parse image pixel RGB
	printImagePixels(input, outfile_stream);

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
}

void printUsage(){
	// [Usage] Correctly use Project9
	// ------------------------------
	cerr << "Usage:\n" << setw(40) << left << "    ./a.out [filename] [options]" << "Specify filename of image to read" << endl;
	cerr << endl;
	cerr << setw(20) << left << "Arguments:" << endl;
	cerr << setw(20) << left << "    -f [filename]" << "Specify filename of image to read" << endl;
	
	return;
}
