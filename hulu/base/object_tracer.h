#pragma once
#ifndef _HULU_OBJECT_TRACER_H_
#define _HULU_OBJECT_TRACER_H_

#include "../gvals.h"
#include <map>
#include <chrono>

_HULU_BEGIN

struct Alloc_record
{
	void* addr;
	size_t size;
	std::chrono::system_clock stamp;
};

template <typename _Traced_type>
class Object_tracer
{
	
};

_HULU_END

#endif // _HULU_OBJECT_TRACER_H_