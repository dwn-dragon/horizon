#if !defined(ENV_INLINE_DEF)
#if defined(LOCAL_INLINE)
#undef LOCAL_INLINE
#endif
#define LOCAL_INLINE inline
#endif

template< class Ty, class Fn >
LOCAL_INLINE size_t ENV_NSPC::trimStart(Ty&& str, Fn&& fn, ENV_NSPC::Range rng) {
	size_t i = rng.start;
	//	keeps going forward until invalid character or end of string
	for (; i < rng.end; i++)
		if (!static_cast<bool>(fn(str[i])))
			//	invalid character
			break;
	//	returns last position
	return i;
}
template< class Ty, class Fn >
LOCAL_INLINE size_t ENV_NSPC::trimEnd(Ty&& str, Fn&& fn, ENV_NSPC::Range rng) {
	size_t i = rng.end;
	//	keeps going back until invalid character or start of string
	for (; i > rng.start; i--)
		if (!static_cast<bool>(fn(str[i - 1])))
			//	invalid character
			break;
	//	returns last position
	return i;
}

template< class Ty, class Fn >
LOCAL_INLINE ENV_NSPC::Range ENV_NSPC::trim(Ty&& str, Fn&& fn, ENV_NSPC::Range rng) {
	//	results
	ENV_NSPC::Range res{ rng };
	//	start
	res.start = trimStart(str, fn, res);
	//	end
	res.end = trimEnd(str, fn, res);
	//	returns values
	return res;
}

template <class Ty, class Fn>
LOCAL_INLINE ENV_NSPC::Range ENV_NSPC::parse(Ty &&str, Fn &&fn, ENV_NSPC::Range range) {
	ENV_NSPC::Range res;
	//	starts at range start
	res.start = range.start;
	while (res.start < range.end) {
		//	keeps going until a valid character is found
		if (static_cast<bool>(fn(str[res.start])))
			break;
		//	increases after checks
		res.start++;
	}
	//	starts at word start
	res.end = res.start;
	while (res.end < range.end) {
		//	increases before checks
		res.end++;
		//	keeps going until an invalid character is found
		if (!static_cast<bool>(fn(str[res.end])))
			break;
	}
	//	returns res
	return res;
}

#if !defined( ENV_INLINE_DEF )
#undef LOCAL_INLINE
#endif
