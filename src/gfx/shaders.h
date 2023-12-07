#pragma once

#ifndef HRZ_GFX_SHADERS_INCLUDE
#define HRZ_GFX_SHADERS_INCLUDE

#include "core.h"

#include <stdexcept>

namespace gfx
{
		
	class compilation_error
		: public std::logic_error
	{
	public:
		compilation_error(std::string str)
			: std::logic_error(str) {
		}
	};

	class linkage_error
		: public std::logic_error
	{
	public:
		linkage_error(std::string str)
			: std::logic_error(str) {
		}
	};

	class Shader
	{
		enum Type : uint8_t
		{
			VERTEX,
			GEOMETRY,
			FRAGMENT,
			PROGRAM
		};

		using const_char_ptr = const char*;
		static constexpr const_char_ptr TYPE_NAME[] {
			"VERTEX",
			"GEOMETRY",
			"FRAGMENT",
			"PROGRAM"
		};

		static void _check(GLuint obj, Type type);
		static void _check_compilation(GLuint obj, Type type);
		static void _check_linkange(GLuint obj);

		static std::string _load_code(const char* filepath);
		static GLuint _compile_shader(const std::string& code, Type type);

	public:
		~Shader();
		Shader();

		Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);

		void load(const char* vertexPath, const char* fragmentPath, const char* geometryPath = nullptr);
		void use();

		Shader(const Shader& right) noexcept = default;
		Shader& operator=(const Shader&) noexcept = default;

		Shader(Shader&& right) noexcept;
		Shader& operator=(Shader&& right) noexcept;

		GLuint ID;
	};

}

#endif	//	Include guard
