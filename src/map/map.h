#pragma once

#ifndef INCLUDE_MAP_H
#define INCLUDE_MAP_H

#include "env.h"

#include <memory>
#include <cstdint>

namespace ENV_NSPC
{

	class Facility
	{
	public:
		~Facility() = default;
		Facility() noexcept;
	
		class Door;
		class Room;

		using INDEX = uint16_t;

		Room& room(INDEX ind);
		Door& door(INDEX ind);

		//	sizes
		size_t _dc, _rc;
		//	place structure
		std::unique_ptr<Door[]> _ds;
		std::unique_ptr<Room[]> _rs;
	};

	class Facility::Door
	{
	public:
		~Door() = default;
		Door() noexcept;

		INDEX _rs[2];
	};

	class Facility::Room
	{
	public:
		~Room() = default;

		Room() noexcept;
		Room(size_t dc);

		size_t _dc;
		std::unique_ptr<INDEX[]> _ds;
	};

}

#endif	//	Include guard
