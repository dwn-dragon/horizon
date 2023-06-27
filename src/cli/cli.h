#pragma once

#ifndef INCLUDE_IO_H
#define INCLUDE_IO_H

#include "env.h"

#include "strman.h"

#include <istream>
#include <functional>

namespace ENV_NSPC
{

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
		horizon::Range cut(Fn&& fn);

		horizon::Range range;
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

#include "cli.hpp"

#endif	//	Include guard
