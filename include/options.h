/* Parse command-line options using Boost library
 *
 * Options:
 * 	-f <filename>			Input image filename (query)
 * 	-o <filename>			Output text file for image dimensions & RGB pixels
 * 	-d						Display the input image
*/

#ifndef PROGRAM_OPTIONS_H
#define PROGRAM_OPTIONS_H


// Initiate struct program_options to false
typedef struct program_options {
    bool flag_display		= false;
    bool flag_input_file	= false;
    bool flag_output_file	= false;
	bool flag_threshold		= false;
    std::string	input_file	= "";
    std::string output_file	= "";
	double threshold		= 0.0;
} program_options;

program_options boostPrintUsage(int argc, char** argv);
int boostPrintUsage(int help_code);

#endif
