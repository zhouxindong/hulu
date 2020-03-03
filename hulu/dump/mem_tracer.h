#pragma once
#ifndef _HULU_DUMP_MEM_TRACER_H_
#define _HULU_DUMP_MEM_TRACER_H_

#include "../gvals.h"

#include <string>
#include <ostream>
#include <iomanip>

#pragma warning(disable:4595 4291 4005) 

_HULU_BEGIN

/**
 * @brief record the info of memory allocate
 */
struct Alloc_rec
{
	void* addr;
	std::string file;
	int line;
	size_t size;
};

inline
std::ostream&
operator << (std::ostream& out, Alloc_rec const& r) noexcept
{
	out << "Addr:" << std::setw(16) << r.addr << " - Size: "
		<< r.size << " allocated in " << r.file << ":"
		<< r.line << "\n";
	return out;
}

class Alloc_tracer
{

};


_HULU_END

#endif // _HULU_DUMP_MEM_TRACER_H_