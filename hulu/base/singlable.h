#pragma once
#ifndef _HULU_BASE_SINGLABLE_H_
#define _HULU_BASE_SINGLABLE_H_

#include "../gvals.h"
#include <mutex>

_HULU_BEGIN

/**
 * @brief limit _Wrap_type can only one instance at the same time
 */
template <typename _Wrap_type>
class Singlable
{
public:
	template <typename... Args>
	static _Wrap_type& inst_obj(Args&&... args)
	{
		return *instance_(std::forward<Args>(args)...);
	}

	template <typename... Args>
	static _Wrap_type* inst_ptr(Args&&... args)
	{
		return instance_(std::forward<Args>(args)...);
	}

	Singlable() = delete;

private:
	static _Wrap_type* s_instance_ptr;
	static char* s_place;
	static std::mutex s_mutex;

	template <typename... Args>
	static _Wrap_type* instance_(Args&&... args)
	{
		if (s_instance_ptr == nullptr)
		{
			std::lock_guard<std::mutex> lock(s_mutex);
			if (s_instance_ptr == nullptr)
			{
				alloc_();
				new (s_place) _Wrap_type(std::forward<Args>(args)...);
				s_instance_ptr = reinterpret_cast<_Wrap_type*>(s_place);
				std::atexit(&Singlable::free_);
			}
		}
		return s_instance_ptr;
	}

	static void alloc_()
	{
		s_place = new char[sizeof(_Wrap_type)];
	}

	static void free_()
	{
		(reinterpret_cast<_Wrap_type*>(s_place))->~_Wrap_type();
		delete[] s_place;
	}
};

template <typename _Wrap_type>
_Wrap_type* Singlable<_Wrap_type>::s_instance_ptr = nullptr;

template <typename _Wrap_type>
char* Singlable<_Wrap_type>::s_place = nullptr;

template <typename _Wrap_type>
std::mutex Singlable<_Wrap_type>::s_mutex;

_HULU_END

#endif // _HULU_BASE_SINGLABLE_H_