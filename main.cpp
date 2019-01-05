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
*/

#include <iostream>
#include <iomanip>
#include <string.h>
#include <unistd.h>
#include <Magick++.h>
#include "magick.h"

class Pixel{
	public:
		long red;
		long blue;
		long green;
};

using namespace std;

void printUsage(){
	// [Usage] Correctly use Project9
	// ------------------------------
	cerr << "Usage:\n" << setw(40) << left << "    ./a.out [filename] [options]" << "Specify filename of image to read" << endl;
	cerr << endl;
	cerr << setw(20) << left << "Arguments:" << endl;
	cerr << setw(20) << left << "    -f [filename]" << "Specify filename of image to read" << endl;
	
	return;
}

int main (int argc, char** argv){

	
	Magick::InitializeMagick(*argv);	// Initialize Magick++ API

	// Using getopt to parse input arguments
	// -------------------------------------
	int opt;
	string input = "";

	if ( (argc <= 1) || (argv[argc-1] == NULL) || (argv[argc-1][0] == '-') ){ // Retrieve the non-option argument
		cerr << "No arguments given!" << endl;
		printUsage();
	}else{
		input = argv[argc-1];
	}

	// Display arguments passed to shell
	// ---------------------------------
	for(int i=0; i<argc; i++){
		cout << "Argument " << i << ":\t" << argv[i] << endl;
	}

	cout << "Input:\t" << input << endl; // Check argument options provided

	opterr = 0;	// Turn off getopt error messages (default case)

	while ( (opt = getopt(argc, argv, "f:")) != -1) {	// Retreive options
		switch(opt){
			case 'f':
				if(optarg) input = optarg;
				cout << "[GETOPT] input = " << input << endl;
				break;
			case '?':
				cerr << "Unknown option: " << char(optopt) << endl;
				exit(1);
				break;
			}
	}

	cout << "Input:\t" << input << endl;	// Check argument options provided

	Magick::Image image(input);

	// Call Magick++ RGB Pixel reader
	// ------------------------------
	vector<int> dims = getImageDimensions(image);
	int cols = getImageColumns(image);
	int rows = getImageRows(image);

	// Display Magick++ call results
	//------------------------------
	cout << setw(25) << left << "Dimensions:" << "[" << dims[0] << ", " << dims[1] << "]" << endl;
	cout << setw(25) << left << "Rows:" << rows << endl;
	cout << setw(25) << left << "Columns:" << cols << endl;

	// Parse image pixel RGB

	return 0;
}
