#pragma once
#ifndef _HULU_LOKI_TYPEINFO_H_
#define _HULU_LOKI_TYPEINFO_H_

#include "../gvals.h"
#include <typeinfo>

_HULU_BEGIN

class TypeInfo
{
public:
	TypeInfo();
	TypeInfo(const std::type_info&);
	TypeInfo(const TypeInfo&);
	TypeInfo& operator=(const TypeInfo&);
	
	bool before(const TypeInfo&) const;
	const char* name() const;
private:
	const std::type_info* pInfo_;
};

bool operator==(const TypeInfo&, const TypeInfo&);
bool operator!=(const TypeInfo&, const TypeInfo&);
bool operator<(const TypeInfo&, const TypeInfo&);
bool operator<=(const TypeInfo&, const TypeInfo&);
bool operator>(const TypeInfo&, const TypeInfo&);
bool operator>=(const TypeInfo&, const TypeInfo&);

_HULU_END

#endif /* _HULU_LOKI_TYPEINFO_H_ */