#include <iostream>
#include <stdexcept>
#include <string>
#include <fstream>
#include "fungi.h"
#include "args.hxx"

int main(int argc, const char* argv[]){
	args::ArgumentParser parser("Befunge interpreter", "");
	args::HelpFlag help(parser, "help", "Display this help menu", {'h', "help"});
	args::Group required(parser, "", args::Group::Validators::AtLeastOne);
	args::Positional<std::string> input_file(required, "input file", "The source file");

	// Don't show that "-- can be used to terminate.." thing
	parser.helpParams.showTerminator = false;

	try
	{
		parser.ParseCLI(argc, argv);
	}
	// Display help menu
	catch(args::Help)
	{
		std::cout << parser;
		return 0;
	}
	// Some args related error
	catch (args::ParseError e)
	{
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}
	// Some args validation related error
	catch (args::ValidationError e)
	{

		if(!input_file)
		{
			std::cerr << "No input file\n" << std::endl;
			std::cerr << parser;
			return 1;
		}
		std::cerr << e.what() << std::endl;
		std::cerr << parser;
		return 1;
	}

	// Get file contents
	std::string contents;
	std::stringstream buffer;
	std::ifstream fp(args::get(input_file));
	if(fp.fail()){
		std::cerr<<"Could not open file "+input_file<<std::endl;
	}
	buffer << fp.rdbuf();
	contents = buffer.str();
	fp.close();

	// Run file
	Fungi fungi(contents);
	fungi.run();


	return 0;

}
	
