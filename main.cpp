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

#include<iostream>
#include<iomanip>

using namespace std;

int main (int argc, char** argv){

	if(argc < 2){
		cerr << "Usage:\n" << setw(40) << left << "    ./a.out [filename] [options]" << "Specify filename of image to read" << endl;
		cerr << endl;
		cerr << setw(20) << left << "Arguments:" << endl;
		cerr << setw(20) << left << "    -f [filename]" << "Specify filename of image to read" << endl;

		return 1;	// exit on improper usage
	}


	// Display arguments passed to shell
	// ---------------------------------
	cout << "Argument 0:\t" << argv[0] << endl;
	cout << "Argument 1:\t" << argv[1] << endl;

	return 0;
}
