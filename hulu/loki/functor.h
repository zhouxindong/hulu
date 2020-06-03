#pragma once
#ifndef _HULU_LOKI_FUNCTOR_H_
#define _HULU_LOKI_FUNCTOR_H_

#include "../gvals.h"
#include <memory>

_HULU_BEGIN

template <typename T>
class FunctorImpl;

template <typename R, typename ...Args>
class FunctorImpl<R(Args...)>
{
public:
	virtual R operator()(Args...) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template <typename T>
class Functor;

template <typename R, typename ...Args>
class Functor<R(Args...)>
{
public:
	Functor();
	Functor(const Functor&);
	Functor& operator=(const Functor&);
	explicit Functor(std::shared_ptr<Impl> impl);

	~

private:
	typedef FunctorImpl<R(Args...)> Impl;
	std::shared_ptr<Impl> spImpl_;
};

_HULU_END

#endif /* _HULU_LOKI_FUNCTOR_H_ */