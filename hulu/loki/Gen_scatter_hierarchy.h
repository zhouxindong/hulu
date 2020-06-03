#pragma once

#ifndef _HULU_LOKI_GEN_SCATTER_HIERARCHY_H_
#define _HULU_LOKI_GEN_SCATTER_HIERARCHY_H_

#include "../gvals.h"
#include "Typelist.h"
#include "Int2Type.h"

_HULU_BEGIN

template <typename List, template <typename> class Unit>
class Gen_scatter_hierarchy;

template <typename ...Elements, template <typename> class Unit>
class Gen_scatter_hierarchy<Typelist<Elements...>, Unit>
	: public Gen_scatter_hierarchy<Elements, Unit>...
{
};

template <typename AtomicType, template <typename> class Unit>
class Gen_scatter_hierarchy : public Unit<AtomicType>
{
};

template <template <typename> class Unit>
class Gen_scatter_hierarchy<Typelist<>, Unit>
{
};

/**
 * 利用派生类到基类的隐式转换
 */
template <typename T, typename List, template <typename> class Unit>
Unit<T>& Field(Gen_scatter_hierarchy<List, Unit>& obj)
{
	return obj;
}

/**
 * 基于类型位置索引的基类子对象获取(利用编译期类型分派)
 */
template <typename Head, typename ...Tail, template <typename> class Unit>
Unit<Head>& FieldHelper(
	Gen_scatter_hierarchy<Typelist<Head, Tail...>, Unit>& obj,
	Int2Type<0>
)
{
	Gen_scatter_hierarchy<Head, Unit>& leftBase = obj;
	return leftBase;
}

template <int i, typename Head, typename ...Tail, template <typename> class Unit>
Unit<Typelist_at_t<Typelist<Head, Tail...>, i>>& 
FieldHelper(
	Gen_scatter_hierarchy<Typelist<Head, Tail...>, Unit>& obj,
	Int2Type<i>
)
{
	Gen_scatter_hierarchy<Typelist<Tail...>, Unit>& rightBase = obj;
	return FieldHelper(rightBase, Int2Type<i - 1>());
}

template <int i, typename Head, typename ...Tail, template <typename> class Unit>
Unit<Typelist_at_t<Typelist<Head, Tail...>, i>>&
Field(Gen_scatter_hierarchy<Typelist<Head, Tail...>, Unit>& obj)
{
	return FieldHelper(obj, Int2Type<i>());
}

_HULU_END

#endif /* _HULU_LOKI_GEN_SCATTER_HIERARCHY_H_ */