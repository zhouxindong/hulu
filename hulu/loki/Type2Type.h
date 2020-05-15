#pragma once
#ifndef _HULU_LOKI_TYPE2TYPE_H_
#define _HULU_LOKI_TYPE2TYPE_H_

#include "../gvals.h"

_HULU_BEGIN

template <typename T>
struct Type2Type
{
	typedef T OriginalType;
};

_HULU_END

#endif /* _HULU_LOKI_TYPE2TYPE_H_ */