#pragma once
#ifndef _HULU_LOKI_INT2TYPE_H_
#define _HULU_LOKI_INT2TYPE_H_

#include "../gvals.h"

_HULU_BEGIN

template <int V>
struct Int2Type
{
	enum { value = V };
};

_HULU_END

#endif /* _HULU_LOKI_INT2TYPE_H_ */