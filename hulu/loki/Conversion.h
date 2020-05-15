#pragma once
#ifndef _HULU_LOKI_CONVERSION_H_
#define _HULU_LOKI_CONVERSION_H_

#include "../gvals.h"

_HULU_BEGIN

template <class T, class U>
class Conversion
{
	typedef char Small;
	class Big { char dummy[2]; };
	static Small Test(U);
	static Big Test(...);
	static T MakeT();

public:
	enum { exists = sizeof(Test(MakeT())) == sizeof(Small) };
	enum { exists2Way = exists && Conversion<U, T>::exists };
	enum { sameType = false };
};

template <class T>
class Conversion<T, T>
{
public:
	enum { exists = 1, exists2Way = 1, sameType = 1 };
};

_HULU_END

#endif /* _HULU_LOKI_CONVERSION_H_ */