#pragma once

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include <string>
#include <istream>
#include <functional>

namespace io
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
	size_t trimStart(Ty&& str, Fn&& fn, io::Range range);
	template< class Ty, class Fn >
	size_t trimEnd(Ty&& str, Fn&& fn, io::Range range);

	template< class Ty, class Fn >
	io::Range trim(Ty&& str, Fn&& fn, io::Range range);

	template< class Ty, class Fn >
	io::Range parse(Ty&& str, Fn&& fn, io::Range range);

	//	
	//	Command-Line Interface
	//

	class Line
	{
		static constexpr bool _noex_cstr_def = noexcept(std::string{});
		static constexpr bool _noex_cstr_str_mov = noexcept(std::string{std::move(std::declval<std::string>())});

	public:
		~Line() = default;

		Line() noexcept( _noex_cstr_def );
		Line(std::string&& str) noexcept( _noex_cstr_str_mov );

		template< class Fn >
		void trim(Fn&& fn);
		template< class Fn >
		io::Range cut(Fn&& fn);

		io::Range range;
		std::string line;	
	};

	using LineListener = std::function<void(Line)>;

	class CLI
	{
	public:
		~CLI() = default;
		CLI() noexcept;

		bool start();

		LineListener listener;
		std::istream in;

	private:
		std::string _readLine();
	};

}

#include "io.hpp"

#endif	//	Include guard
