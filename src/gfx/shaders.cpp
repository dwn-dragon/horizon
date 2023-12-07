#include "shaders.h"

#include <fstream>
#include <sstream>
#include <iostream>

constexpr size_t BUFFER_SIZE = 1024;

void gfx::Shader::_check(GLuint shader, Type type) {
	if (type == PROGRAM)
		_check_linkange(shader);
	else
		_check_compilation(shader, type);
}
void gfx::Shader::_check_linkange(GLuint program) {
	GLint res;
	glGetProgramiv(program, GL_LINK_STATUS, &res);
	if (res) return;

	std::string ex = std::string() + TYPE_NAME[PROGRAM] + " linkage error: ";

	GLint max_len = 0;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &max_len);
	if (max_len <= 0)
		throw linkage_error(ex + "UNKNOWN");

	auto buffer = std::make_unique<char[]>(max_len);
	glGetProgramInfoLog(program, max_len, nullptr, buffer.get());
	throw linkage_error(ex + buffer.get());
}
void gfx::Shader::_check_compilation(GLuint shader, Type type) {
	GLint res;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &res);
	if (res) return;

	std::string ex = std::string() + TYPE_NAME[type] + " compilation error: ";

	GLint max_len = 0;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &max_len);
	if (max_len <= 0)
		throw compilation_error(ex + "UNKNOWN");

	auto buffer = std::make_unique<char[]>(max_len);
	glGetShaderInfoLog(shader, BUFFER_SIZE, nullptr, buffer.get());
	throw compilation_error(ex + buffer.get());
}

std::string gfx::Shader::_load_code(const char* filepath) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit | std::ifstream::badbit);

	try {
		//  open the file
		file.open(filepath);

		//  read the file
		std::stringstream ss;
		ss << file.rdbuf();

		file.close();

		//  return the result
		return ss.str();
	}
	catch (const std::ifstream::failure&) {
		throw;
	};
}
GLuint gfx::Shader::_compile_shader(const std::string& code, Type type) {
	GLuint shader = 0;
	switch (type)
	{
	case Shader::VERTEX:
		shader = glCreateShader(GL_VERTEX_SHADER);
		break;
	case Shader::GEOMETRY:
		shader = glCreateShader(GL_GEOMETRY_SHADER);
		break;
	case Shader::FRAGMENT:
		shader = glCreateShader(GL_FRAGMENT_SHADER);
		break;

	case Shader::PROGRAM:
	default:
		throw std::invalid_argument(std::string() + "invalid type \"" + TYPE_NAME[type] + "\"");
	}

	const char* _code = code.c_str();

	glShaderSource(shader, 1, &_code, nullptr);
	glCompileShader(shader);
	_check(shader, type);

	return shader;
}

gfx::Shader::~Shader() {
	glDeleteProgram(ID);
}
gfx::Shader::Shader()
	: ID(0) {
}

gfx::Shader::Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	load(vertexPath, fragmentPath, geometryPath);
}

void gfx::Shader::load(const char* vertexPath, const char* fragmentPath, const char* geometryPath) {
	GLuint vertex = 0, geometry = 0, fragment = 0;

	try {
		vertex = _compile_shader(_load_code(vertexPath), VERTEX);
		fragment = _compile_shader(_load_code(fragmentPath), FRAGMENT);
		if (geometryPath != nullptr)
			geometry = _compile_shader(_load_code(geometryPath), GEOMETRY);
	}
	catch (std::ifstream::failure& e) {
		throw std::runtime_error(std::string("[ERROR] File reading failure: ") + e.what());
	}
	catch (...) {
		throw;
	}

	ID = glCreateProgram();
	glAttachShader(ID, vertex);
	glAttachShader(ID, fragment);
	if (geometryPath != nullptr)
		glAttachShader(ID, geometry);

	glLinkProgram(ID);
	_check(ID, PROGRAM);

	glDeleteShader(vertex);
	glDeleteShader(fragment);
	if (geometryPath != nullptr)
		glDeleteShader(geometry);
}

void gfx::Shader::use() {
	glUseProgram(ID);
}

gfx::Shader::Shader(gfx::Shader&& right) noexcept 
	: ID(right.ID) {
	right.ID = 0;
}
gfx::Shader& gfx::Shader::operator=(gfx::Shader&& right) noexcept {
	if (ID != 0)
		glDeleteProgram(ID);
	ID = right.ID;
	right.ID = 0;

	return *this;
}
