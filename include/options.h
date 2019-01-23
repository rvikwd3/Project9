/* Parse command-line options using Boost library
 *
 * Options:
 * 	-f <filename>			Input image filename (query)
 * 	-o <filename>			Output text file for image dimensions & RGB pixels
 * 	-d						Display the input image
*/

#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H

#define HELP_CODE 0xff

// Initiate struct program_options to false
typedef struct program_options {
	bool flag_display		= false;
	bool flag_input_file	= false;
	bool flag_output_file	= false;
	std::string	input_file	= "";
	std::string output_file	= "";
} program_options;

program_options boostPrintUsage(int argc, char** argv);
int boostPrintUsage(int help_code);

#endif
