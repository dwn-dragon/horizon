#include "cli.h"

#if !defined(ENV_INLINE_DEF)
#if defined(LOCAL_INLINE)
#undef LOCAL_INLINE
#endif
#define LOCAL_INLINE
#endif

LOCAL_INLINE size_t ENV_NSPC::Range::length() noexcept {
	return end - start;	
}
LOCAL_INLINE std::string ENV_NSPC::Range::substr(const std::string& str) {
	return str.substr(start, length());
}

LOCAL_INLINE ENV_NSPC::Line::Line() noexcept( _noex_cstr_def )
	: line{ } {
	range = ENV_NSPC::Range{ 0, line.length() };
}
LOCAL_INLINE ENV_NSPC::Line::Line(std::string &&str) noexcept( _noex_cstr_str_mov )
	: line{ std::move(str) } {
	range = ENV_NSPC::Range{ 0, line.length() };
}

LOCAL_INLINE ENV_NSPC::CLI::CLI() noexcept
	: in{ nullptr }, listener{ nullptr } {
}

LOCAL_INLINE bool ENV_NSPC::CLI::start() {
	//	invalid input stream
	if (!in.good())
		return false;
	//	invalid listener
	if (!static_cast<bool>(listener))
		return false;

	//	keeps going
	while (true) {
		std::string str = _readLine();

		Line line{ std::move(str) };
		line.trim(std::isspace);

		listener(std::move(line));
	}

	//	returns true at the end
	return true;
}
LOCAL_INLINE std::string ENV_NSPC::CLI::_readLine() {
	std::string res;
	std::getline(in, res);

	return std::move(res);
}

#if !defined( ENV_INLINE_DEF )
#undef LOCAL_INLINE
#endif
