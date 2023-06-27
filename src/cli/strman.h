#pragma once

#ifndef INCLUDE_STRINGS_H
#define INCLUDE_STRINGS_H

#include "env.h"

#include <string>

namespace ENV_NSPC
{

	struct Range
	{
		size_t start, end;

		size_t length() noexcept;
		std::string substr(const std::string& str);
	};

	//
	//	String manipulation
	//

	template< class Ty, class Fn >
	size_t trimStart(Ty&& str, Fn&& fn, Range range);
	template< class Ty, class Fn >
	size_t trimEnd(Ty&& str, Fn&& fn, Range range);

	template< class Ty, class Fn >
	Range trim(Ty&& str, Fn&& fn, Range range);

	template< class Ty, class Fn >
	Range parse(Ty&& str, Fn&& fn, Range range);

}

#include "strman.hpp"

#endif	//	Include guard
