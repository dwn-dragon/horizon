#include "io.h"
#include <iostream>

int main(int argc, char const *argv[]) {
	io::CLI cli;

	cli.in.rdbuf( std::cin.rdbuf() );
	cli.in.clear();

	cli.listener = [](io::Line line) {
		auto cmd = line.cut(std::isgraph);

		std::cout << "Command: \"" << cmd.substr(line.line) << "\"\n";
		std::cout << "Args: \"" << line.range.substr(line.line) << "\"";
		
		std::cout << std::endl;
	};

	if (!cli.start()) {
		std::cout << "Error";
		return 1;	
	}

	return 0;
}
