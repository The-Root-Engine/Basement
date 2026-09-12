// Root Engine / Basement

#pragma once

#include "../Basement.h"

template<usize Index, typename T>
struct TTupleLeaf
{
	T Value;
	template<typename U>
	constexpr TTupleLeaf(U&& InValue) : Value(Forward<U>(InValue)) {}
};

template<usize Index, typename... Types>               struct TTupleElement;
template<usize Index, typename Head, typename... Tail> struct TTupleElement<Index, Head, Tail...> : TTupleElement<Index - 1, Tail...> {};
template<typename Head, typename... Tail>               struct TTupleElement<    0, Head, Tail...> { using Type = Head; };

template<typename IndexSequence, typename... Types>
struct TTuplePrivate;

template<usize... Indices, typename... Types>
struct TTuplePrivate<Meta::IndexSequence<Indices...>, Types...> : public TTupleLeaf<Indices, Types>... 
{
	template<typename... Args>
	constexpr TTuplePrivate(Args&&... InArgs) : TTupleLeaf<Indices, Types>(Forward<Args>(InArgs))... {}
};

template<typename... Types>
class TTuple : public TTuplePrivate<Meta::MakeIndexSequence<sizeof...(Types)>, Types...>
{
	using Super = TTuplePrivate<Meta::MakeIndexSequence<sizeof...(Types)>, Types...>;

public:
	template<typename... Args> constexpr TTuple(Args&&... InArgs) : Super(Forward<Args>(InArgs)...) {}
	
	static constexpr usize Size = sizeof...(Types);
	constexpr usize Num() const { return Size; }
	
	template<usize Index> constexpr /* */ auto& Get() /* */ { return static_cast</* */ TTupleLeaf<Index, typename TTupleElement<Index, Types...>::Type>&>(*this).Value; }
	template<usize Index> constexpr const auto& Get() const { return static_cast<const TTupleLeaf<Index, typename TTupleElement<Index, Types...>::Type>&>(*this).Value; }
};
