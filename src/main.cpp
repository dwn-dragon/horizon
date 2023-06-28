#include "cli/cli.h"
#include "map/map.h"

#include <iostream>
#include <iomanip>

int main(int argc, char const *argv[]) {
	//	Map
	horizon::Facility facility;
	//	allocs mem for doors
	facility._dc = 2;
	facility._ds = std::make_unique<horizon::Facility::Door[]>(facility._dc);
	//	door 0	connects 0 and 1
	facility._ds[0]._rs[0] = 0;
	facility._ds[0]._rs[1] = 1;
	//	door 1	connects 0 and 2
	facility._ds[1]._rs[0] = 0;
	facility._ds[1]._rs[1] = 2;
	//	allocs mem for rooms
	facility._rc = 3;
	facility._rs = std::make_unique<horizon::Facility::Room[]>(facility._rc);
	//	allocs mem for doors
	facility._rs[0]._dc = 2;
	facility._rs[0]._ds = std::make_unique<horizon::Facility::INDEX[]>(facility._rs[0]._dc);
	//	sets door 0
	facility._rs[0]._ds[0] = 0;
	//	sets door 1
	facility._rs[0]._ds[1] = 1;
	//	allocs mem for doors
	facility._rs[1]._dc = 1;
	facility._rs[1]._ds = std::make_unique<horizon::Facility::INDEX[]>(facility._rs[0]._dc);
	//	sets door 0
	facility._rs[1]._ds[0] = 0;
	//	allocs mem for doors
	facility._rs[2]._dc = 1;
	facility._rs[2]._ds = std::make_unique<horizon::Facility::INDEX[]>(facility._rs[0]._dc);
	//	sets door 1
	facility._rs[2]._ds[0] = 1;

	//	Command Line Interface
	horizon::CLI cli;
	horizon::Facility::INDEX pos = 0;

	std::cout << std::fixed << std::setfill('0');

	cli.in.rdbuf( std::cin.rdbuf() );
	cli.in.clear();

	cli.listener = [&facility, &pos](horizon::Line line) {
		auto cmd = line.cut(std::isgraph);
		auto scmd = cmd.substr(line.line);

		if (scmd == "look") {
			//	next arg
			auto arg = line.cut(std::isgraph);
			auto sarg = arg.substr(line.line);

			if (sarg == "around") {
				auto& room = facility._rs[pos];
				std::cout << "The room has " << room._dc << " doors" << std::endl;
			}
			else if (sarg == "at") {
				auto arg = line.cut(std::isgraph);
				auto sarg = arg.substr(line.line);

				if (sarg == "door") {
					auto arg = line.cut(std::isgraph);
					auto sarg = arg.substr(line.line);

					try {
						auto ind = std::stoi(sarg) - 1;
						auto& room = facility._rs[pos];

						if (ind > room._dc)
							std::cout << "The room doesn't have that many doors" << std::endl;
						else {
							std::cout << "That's Door #" << std::setw(5) << room._ds[ind] << std::endl;
						}
					}
					catch (const std::exception& err) {
						std::cerr << err.what() << std::endl;
					}
				}
			}
			else {
				std::cout << arg.start << "\t" << arg.end << std::endl;
				std::cout << "Invalid argument \"" << arg.substr(line.line) << "\"" << std::endl;
			}
		}
		else if (scmd == "move") {
			auto arg = line.cut(std::isgraph);
			auto sarg = arg.substr(line.line);

			if (sarg == "thro") {
				auto arg = line.cut(std::isgraph);
				auto sarg = arg.substr(line.line);

				if (sarg == "door") {
					auto arg = line.cut(std::isgraph);
					auto sarg = arg.substr(line.line);

					try {
						auto ind = std::stoi(sarg) - 1;
						auto& room = facility._rs[pos];

						if (ind > room._dc)
							std::cout << "The room doesn't have that many doors" << std::endl;
						else {
							auto& door = facility._ds[room._ds[ind]];
							horizon::Facility::INDEX next;

							if (door._rs[0] != pos)
								next = door._rs[0];
							if (door._rs[1] != pos)
								next = door._rs[1];

							pos = next;
							std::cout << "You moved to Room #" << std::setw(5) << next << std::endl;
						}
					}
					catch (const std::exception& err) {
						std::cerr << err.what() << std::endl;
					}
				}
			}
		}
		else {
			std::cout << "Command: \"" << cmd.substr(line.line) << "\" not recognized" << std::endl;
		}
	};

	if (!cli.start()) {
		std::cout << "Error";
		return 1;	
	}

	return 0;
}
