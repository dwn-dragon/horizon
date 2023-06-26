#if !defined(ENV_INLINE_DEF)
#if defined(LOCAL_INLINE)
#undef LOCAL_INLINE
#endif
#define LOCAL_INLINE inline
#endif

template< class Fn >
LOCAL_INLINE void ENV_NSPC::Line::trim(Fn&& fn) {
	range = ENV_NSPC::trim(line, std::forward<Fn>(fn), range);
}
template< class Fn >
LOCAL_INLINE ENV_NSPC::Range ENV_NSPC::Line::cut(Fn&& fn) {
	auto res = parse(line, std::forward<Fn>(fn), range);
	range.start = res.end;
	return res;
}

#if !defined( ENV_INLINE_DEF )
#undef LOCAL_INLINE
#endif
