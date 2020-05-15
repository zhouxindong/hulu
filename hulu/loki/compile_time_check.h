#pragma once
#ifndef _HULU_LOKI_COMPILE_TIME_CHECK_H_
#define _HULU_LOKI_COMPILE_TIME_CHECK_H_

#include "../gvals.h"

_HULU_BEGIN

template <bool>
struct CompileTimeChecker
{
	CompileTimeChecker(...);
};

template <>
struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg)	\
	{\
		class ERROR_##msg {};	\
		(void)sizeof(CompileTimeChecker<(expr)>ERROR_##msg()));	\
	}

_HULU_END

#endif /* _HULU_LOKI_COMPILE_TIME_CHECK_H_ */