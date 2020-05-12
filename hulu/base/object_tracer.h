#pragma once
#ifndef _HULU_OBJECT_TRACER_H_
#define _HULU_OBJECT_TRACER_H_

#include "../gvals.h"

#include <map>
#include <chrono>
#include <string>
#include <type_traits>
#include <sstream>

#include "../chrono/chrono_ex.h"
#include "../dump/stack_tracer.h"

_HULU_BEGIN

/**
 * @brief for arry, ::operator new[] return the address is 
	differenct to new[] expression returned, add 8 bytes
 */
#ifdef _WIN64
	constexpr int64_t kArrayPointOffset = 8;
#else
	constexpr int64_t kArrayPointOffset = 4;
#endif

/**
 * @brief new operator allocate recorder
 */
struct Alloc_record
{
	void* addr;
	size_t size;
	bool is_array;
	std::chrono::system_clock::time_point stamp;
	std::string call_stack;
};

inline
std::ostream&
operator << (std::ostream& out, Alloc_record const& r)
{
	out << "Address: " << std::setw(16) << r.addr << std::endl;
	out << "Is array? " << std::boolalpha << r.is_array << std::noboolalpha << std::endl;
	out << "Size: " << r.size << std::endl;
	out << "Time stamp: " << time_point_to_string(r.stamp) << std::endl;
	out << "Call stack: " /*<< std::endl*/;
	out << r.call_stack << std::endl;
	return out;
}

/**
 * @brief base class for class whose objects can be traced
 * @param _Tx not used, just for only header defined static objects
 */
template <typename _Tx>
class Inst_trace_base_
{
public:
	static void* operator new(size_t size)
	{
		void* p = ::operator new(size);
		s_table.insert(std::make_pair((void*)p, record_((void*)p, size, false)));
		return p;
	}

	static void* operator new[](size_t size)
	{
		void* p = ::operator new[](size);
		s_table.insert(std::make_pair((void*)p, record_((void*)p, size, true)));
		return p;
	}

	static void operator delete(void* p, size_t size)
	{
		auto it = s_table.find(p);
		if (it != s_table.end())
			s_table.erase(p);
		::operator delete(p);
	}

	static void operator delete[](void* p, size_t size)
	{
		auto it = s_table.find(p);
		if (it != s_table.end())
			s_table.erase(p);
		::operator delete[](p);
	}

	template <typename _T, typename = std::enable_if_t<
		std::is_base_of_v<Inst_trace_base_, std::decay_t<_T>>>>
		static void delete_all()
	{
		auto it = s_table.begin();
		while (it != s_table.end())
		{
			(*it).second.is_array ? delete[](_T*)((int64_t)it->first + kArrayPointOffset) :
				delete (_T*)(it->first);
			it = s_table.begin();
		}
	}

	static void print(std::ostream& out)
	{
		int count = 1;
		auto it = s_table.begin();
		while (it != s_table.end())
		{
			if (count != 1)
				out << std::endl;

			out << "No: " << count << std::endl;
			out << it->second;
			++it;
			++count;
		}
	}

	virtual ~Inst_trace_base_() {}

private:
	static Alloc_record record_(void* p, size_t size, bool is_array)
	{
		Alloc_record rec;
		rec.addr = p;
		rec.size = size;
		rec.is_array = is_array;
		rec.stamp = to_local(std::chrono::system_clock::now());
		rec.call_stack = Stack_tracer::stack_trace();
		return rec;
	}

private:
	static std::map<void*, Alloc_record> s_table;
};

template <typename _Tx>
std::map<void*, Alloc_record> Inst_trace_base_<_Tx>::s_table;

using Inst_trace_base = Inst_trace_base_<void>;

_HULU_END

#endif // _HULU_OBJECT_TRACER_H_