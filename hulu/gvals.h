/**
* @file gvals.h
* @brief provide the most basic stand for each head file defined in hulu
* @details nothing
* @author zhouxindong
* @email 13611050407@139.com
* @version V1.0
* @date 2020-02-21
*/

#pragma once
#ifndef _HULU_GVALS_H_
#define _HULU_GVALS_H_

/**
* to resolve the redefinitions between WinSock2.h and Windows.h
1. include first WinSock2.h, then Windows.h
2. or #define WIN32_LEAN_AND_MEAN
*/

// 1.
#include <WinSock2.h>
#include <Windows.h>

// 2.
//#define  WIN32_LEAN_AND_MEAN
//#include <Windows.h>

#define _HULU_BEGIN namespace hulu {
#define _HULU_END   }
#define _HULU  ::hulu::

#define _STD_BEGIN namespace std {
#define _STD_END   }
#define _STD ::std::

/*
** defined class data member
** generated data set|get function automatic
** usage: name -> name|set_name (name_)
** readonly means no setter
** _INIT means use initialized value
*/
#pragma region auto_property

#define DEF_PROPERTY_INIT(type, name, value) type name##_{ value };
#define DEF_PROPERTY(type, name) type name##_;

#define GET_PROPERTY(type, name) type name() const {return name##_;}
#define GET_PROPERTY_CONSTREF(type, name) const type & name() const {return name##_;}
#define GET_PROPERTY_REF(type, name) type & name() const {return name##_;}

#define SET_PROPERTY(type, name) void set_##name(const type & value){name##_ = value;}

#define PROPERTY(type, name) \
private:\
	DEF_PROPERTY(type, name) \
public:\
	GET_PROPERTY_CONSTREF(type, name) \
	SET_PROPERTY(type, name)

#define PROPERTY_INIT(type, name, value) \
private:\
	DEF_PROPERTY_INIT(type, name, value) \
public:\
	GET_PROPERTY_CONSTREF(type, name) \
	SET_PROPERTY(type, name)

#define PROPERTY_READONLY(type, name) \
private:\
	DEF_PROPERTY(type, name) \
public:\
	GET_PROPERTY_CONSTREF(type, name)

#define PROPERTY_READONLY_INIT(type, name, value) \
private:\
	DEF_PROPERTY_INIT(type, name, value) \
public:\
	GET_PROPERTY_CONSTREF(type, name)

#pragma endregion

#pragma region stolen from stl

// Definitions of calling conventions used code sometimes compiled as managed
#if defined _M_CEE_PURE || defined MRTDLL
#define __CLRCALL_OR_CDECL __clrcall
#define __CLR_OR_THIS_CALL __clrcall
#else
#define __CLRCALL_OR_CDECL __cdecl
#define __CLR_OR_THIS_CALL
#endif

#ifdef __cplusplus
#define _CSTD	::

#define _EXTERN_C			extern "C" {
#define _END_EXTERN_C		}
#else /* ^^^ __cplusplus ^^^ // vvv !__cplusplus vvv */
#define _CSTD

#define _EXTERN_C
#define _END_EXTERN_C
#endif /* __cplusplus */

#pragma endregion

#endif // _HULU_GVALS_H_