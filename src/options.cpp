#include <boost/program_options.hpp>
#include <iostream>
#include "options.h"
#include "constants.h"

// --------------------------------------------------------------------------------
int boostPrintUsage(int help_code) { // {{{

    namespace po = boost::program_options;

    int return_value;

    if ( help_code == constants::HELP_CODE ) {
        po::options_description desc("Options");
        desc.add_options()
        ("help,h", 			"Show this help message")
        ("input-file,i",	"Specify input file of image to read")
        ("outfile,o",		"Specify filename of text file to write image dimensions & pixel colors")
        ("display,d",		"Display the input image")
        ("threshold,t",		"Decimal threshold for segmentation. Range is positive. (eg 1.2)")
        ;

        std::cout << desc << std::endl;

        return_value = 0;
    } else {
        std::cout << "[OPTIONS]\tWrong help code specified" << std::endl;
        return_value = -1;
    }

    return return_value;
} // }}}
// --------------------------------------------------------------------------------

// --------------------------------------------------------------------------------
program_options boostPrintUsage(int argc, char** argv) { // {{{

    program_options args;

    namespace po = boost::program_options;

    po::options_description desc("Options");
    desc.add_options()
    ("help,h",			"Show this help message")
    ("input-file,i",	po::value<std::string>(),	"Specify input file of image to read")
    ("outfile,o",		po::value<std::string>(),	"Specify filename of text file to write image dimensions & pixel colors")
    ("display,d",		"Display the input image")
	("threshold,t",		po::value<double>(),		"Decimal threshold for segmentation. Range is positive. (eg 1.2)")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if ( vm.count("help") ) {
        std::cout << desc << std::endl;
        return args;
    }

    if ( vm.count("input-file") ) {
        std::cout << "[BOOST]\t" << vm["input-file"].as<std::string>() << std::endl;
        args.flag_input_file	= true;
        args.input_file			= vm["input-file"].as <std::string>();
    }

    if ( vm.count("outfile") ) {
        std::cout << "[BOOST]\t" << vm["outfile"].as<std::string>() << std::endl;
        args.flag_output_file	= true;
        args.output_file		= vm["outfile"].as<std::string>();
    }

    if ( vm.count("display") ) {
        std::cout << "[BOOST]\tDisplay flag triggered" << std::endl;
        args.flag_display = true;
    }

	if ( vm.count("threshold") ) {
		std::cout << "[BOOST]\tThreshold: " << vm["threshold"].as<double>() << std::endl;
		args.flag_threshold		= true;
		args.threshold			= vm["threshold"].as<double>();
	}

    return args;

} // }}}
