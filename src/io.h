#pragma once

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include <iostream>
#include <string>

namespace io
{

	struct Range
	{
		size_t start, end; 
	};

	//
	//	String manipulation
	//

	template< class Ty, class Fn >
	size_t trim_start(Ty&& str, Fn&& fn, io::Range range);
	template< class Ty, class Fn >
	size_t trim_end(Ty&& str, Fn&& fn, io::Range range);

	template< class Ty, class Fn >
	io::Range trim(Ty&& str, Fn&& fn, io::Range range);

	template< class Ty, class Fn >
	io::Range parse(Ty&& str, Fn&& fn, io::Range range);

}

#include "io.hpp"

#endif	//	Include guard
