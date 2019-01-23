#include <boost/program_options.hpp>
#include <iostream>
#include "options.h"

int boostPrintUsage(int help_code){

	namespace po = boost::program_options;

	int return_value;

	if ( help_code == HELP_CODE ){
		po::options_description desc("Options");
		desc.add_options()
			("help,h", 			"Show this help message")
			("input-file,i",	"Specify input file of image to read")
			("outfile,o",		"Specify filename of text file to write image dimensions & pixel colors")
			("display,d",		"Display the input image")
		;

		std::cout << desc << std::endl;

		return_value = 0;
	} else {
		std::cout << "[OPTIONS]\tWrong help code specified" << std::endl;
		return_value = -1;
	}

	return return_value;
}
	

program_options boostPrintUsage(int argc, char** argv){

	program_options args;
	
	namespace po = boost::program_options;

	po::options_description desc("Options");
	desc.add_options()
		("help,h",			"Show this help message")
		("input-file,i",	po::value<std::string>(),	"Specify input file of image to read")
		("outfile,o",		po::value<std::string>(),	"Specify filename of text file to write image dimensions & pixel colors")
		("display,d",		"Display the input image")
	;

	po::variables_map vm;
	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	if ( vm.count("help") ){
		std::cout << desc << std::endl;
		return args;
	}

	if ( vm.count("input-file") ){
		std::cout << "BOOST\n" << vm["input-file"].as<std::string>() << std::endl;
		args.flag_input_file	= true;
		args.input_file			= vm["input-file"].as <std::string>();
	}

	if ( vm.count("outfile") ){
		std::cout << "BOOST\n" << vm["outfile"].as<std::string>() << std::endl;
		args.flag_output_file	= true;
		args.output_file		= vm["outfile"].as<std::string>();
	}

	if ( vm.count("display") ){
		std::cout << "BOOST\nDisplay flag triggered" << std::endl;
		args.flag_display = true;
	}

	return args;

}