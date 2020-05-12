#pragma once
#ifndef _HULU_THREAD_PEER_THREAD_H_
#define _HULU_THREAD_PEER_THREAD_H_

#include "../gvals.h"

#include <thread>
#include <vector>

#include "../base/noncopyable.h"

_HULU_BEGIN

/**
 * @brief threads run same time
 */
template <size_t max_count = 100>
class Peer_threads_
{
public:
	template <typename _Fn, typename... _Args>
	bool create(_Fn&& f, _Args&&... args)
	{
		if (threads_.size() >= 100)
			return false;

		std::thread* t = new std::thread(
			std::forward<_Fn>(f),
			std::forward<_Args>(args)...);
		threads_.push_back(t);
		return true;
	}

	void release()
	{
		for (std::thread* : threads_)
		{

		}
	}

private:
	std::vector<std::thread*> threads_;


};

template <size_t max_count = 100>
using Peer_threads = Non_copyable<Peer_threads_<max_count>>;

_HULU_END

#endif // _HULU_THREAD_PEER_THREAD_H_