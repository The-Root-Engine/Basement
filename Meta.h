// Root Engine / Basement

#pragma once

#include "Aliases/Common.h"

namespace Meta
{
	template<typename...> using Void = void;
	
	struct TrueType  { static constexpr bool Value = true ; constexpr operator bool() const { return true ; } };
	struct FalseType { static constexpr bool Value = false; constexpr operator bool() const { return false; } };

	template<bool Condition, typename T, typename F> struct ConditionalPrivate              { using Type = T; };
	template<typename T, typename F>                 struct ConditionalPrivate<false, T, F> { using Type = F; };
	template<bool Condition, typename T, typename F> using Conditional = typename ConditionalPrivate<Condition, T, F>::Type;

	template<bool Condition, typename T = void> struct EnableIfPrivate {};
	template<typename T>                        struct EnableIfPrivate<true, T> { using Type = T; };
	template<bool Condition, typename T = void> using EnableIf = typename EnableIfPrivate<Condition, T>::Type;

	template<typename T> struct RemoveReferencePrivate      { using Type = T; };
	template<typename T> struct RemoveReferencePrivate<T& > { using Type = T; };
	template<typename T> struct RemoveReferencePrivate<T&&> { using Type = T; };
	template<typename T> using RemoveReference = typename RemoveReferencePrivate<T>::Type;
	
	template<typename T> struct RemoveConstPrivate          { using Type = T; };
	template<typename T> struct RemoveConstPrivate<const T> { using Type = T; };
	template<typename T> using RemoveConst = typename RemoveConstPrivate<T>::Type;

	template<typename T> struct RemoveConstVolatilePrivate                   { using Type = T; };
	template<typename T> struct RemoveConstVolatilePrivate<const T         > { using Type = T; };
	template<typename T> struct RemoveConstVolatilePrivate<volatile T      > { using Type = T; };
	template<typename T> struct RemoveConstVolatilePrivate<const volatile T> { using Type = T; };
	template<typename T> using RemoveConstVolatile = typename RemoveConstVolatilePrivate<T>::Type;

	template<typename T>           struct RemoveExtentPrivate       { using Type = T; };
	template<typename T, usize N> struct RemoveExtentPrivate<T[N]> { using Type = T; };
	template<typename T> using RemoveExtent = typename RemoveExtentPrivate<T>::Type;
	
	template<typename T> struct RemovePointerPrivate     { using Type = T; };
	template<typename T> struct RemovePointerPrivate<T*> { using Type = T; };
	template<typename T> using RemovePointer = typename RemovePointerPrivate<T>::Type;

	template <typename T> struct AddRValueReferencePrivate       { using Type = T&&; };
	template <>           struct AddRValueReferencePrivate<void> { using Type = void; };
	template <typename T> using AddRValueReference = typename AddRValueReferencePrivate<T>::Type;
	template <typename T> AddRValueReference<T> DeclVal() noexcept {}

	template<typename T> struct IsLValueReferencePrivate     : FalseType {};
	template<typename T> struct IsLValueReferencePrivate<T&> : TrueType  {};
	template<typename T> inline constexpr bool IsLValueReference = IsLValueReferencePrivate<T>::Value;

	template<typename T> struct IsRValueReferencePrivate      : FalseType {};
	template<typename T> struct IsRValueReferencePrivate<T&&> : TrueType  {};
	template<typename T> inline constexpr bool IsRValueReference = IsRValueReferencePrivate<T>::Value;

	template<typename T> struct IsReferencePrivate      : FalseType {};
	template<typename T> struct IsReferencePrivate<T& > : TrueType  {};
	template<typename T> struct IsReferencePrivate<T&&> : TrueType  {};
	template<typename T> inline constexpr bool IsReference = IsReferencePrivate<T>::Value;
	
	template<typename T> struct IsConstPrivate          : FalseType {};
	template<typename T> struct IsConstPrivate<const T> : TrueType  {};
	template<typename T> inline constexpr bool IsConst = IsConstPrivate<T>::Value;

	template<typename T> struct IsPointerPrivate           : FalseType {};
	template<typename T> struct IsPointerPrivate<T*      > : TrueType  {};
	template<typename T> struct IsPointerPrivate<T* const> : TrueType  {};
	template<typename T> inline constexpr bool IsPointer = IsPointerPrivate<T>::Value;

	template<typename T, typename U> struct IsSamePrivate       : FalseType {};
	template<typename T>             struct IsSamePrivate<T, T> : TrueType  {};
	template<typename T, typename U> inline constexpr bool IsSame = IsSamePrivate<T, U>::Value;

	template<typename T> struct IsVoidPrivate       : FalseType {};
	template<>           struct IsVoidPrivate<void> : TrueType  {};
	template<typename T> inline constexpr bool IsVoid = IsVoidPrivate<T>::Value;
	
	template<typename T> struct IsIntegerPrivate         : FalseType {};
	template<>           struct IsIntegerPrivate<int8  > : TrueType  {};
	template<>           struct IsIntegerPrivate<int16 > : TrueType  {};
	template<>           struct IsIntegerPrivate<int32 > : TrueType  {};
	template<>           struct IsIntegerPrivate<int64 > : TrueType  {};
	template<>           struct IsIntegerPrivate<uint8 > : TrueType  {};
	template<>           struct IsIntegerPrivate<uint16> : TrueType  {};
	template<>           struct IsIntegerPrivate<uint32> : TrueType  {};
	template<>           struct IsIntegerPrivate<uint64> : TrueType  {};
	template<typename T> inline constexpr bool IsInteger = IsIntegerPrivate<T>::Value;
	
	template<typename T> struct IsFloatingPointPrivate           : FalseType {};
	template<typename T> inline constexpr bool IsFloatingPoint = IsFloatingPointPrivate<T>::Value;
	
	template<typename T> struct IsArithmeticPrivate : Conditional<IsInteger<T> || IsFloatingPoint<T>, TrueType, FalseType> {};
	template<typename T> inline constexpr bool IsArithmetic = IsArithmeticPrivate<T>::Value;
	
	template<typename T> struct IsSignedPrivate        : FalseType {};
	template<>           struct IsSignedPrivate<int8 > : TrueType  {};
	template<>           struct IsSignedPrivate<int16> : TrueType  {};
	template<>           struct IsSignedPrivate<int32> : TrueType  {};
	template<>           struct IsSignedPrivate<int64> : TrueType  {};
	template<typename T> inline constexpr bool IsSigned = IsSignedPrivate<T>::Value;
	
	template<typename T> struct IsUnsignedPrivate         : FalseType {};
	template<>           struct IsUnsignedPrivate<uint8 > : TrueType  {};
	template<>           struct IsUnsignedPrivate<uint16> : TrueType  {};
	template<>           struct IsUnsignedPrivate<uint32> : TrueType  {};
	template<>           struct IsUnsignedPrivate<uint64> : TrueType  {};
	template<typename T> inline constexpr bool IsUnsigned = IsUnsignedPrivate<T>::Value;

	template<typename T>           struct IsArrayPrivate       : FalseType {};
	template<typename T, usize N> struct IsArrayPrivate<T[N]> : TrueType  {};
	template<typename T> inline constexpr bool IsArray = IsArrayPrivate<T>::Value;

	template<typename T>                   struct IsFunctionPrivate             : FalseType {};
	template<typename R, typename... Args> struct IsFunctionPrivate<R(Args...)> : TrueType  {};
	template<typename T> inline constexpr bool IsFunction = IsFunctionPrivate<T>::Value;

	template<typename T>
	struct DecayPrivate
	{
		using RemovedReference = RemoveReference<T>;
		using Type = Conditional<
			IsArray<RemovedReference>,
			RemoveExtent<RemovedReference>*,
			Conditional<
				IsFunction<RemovedReference>,
				RemovedReference*,
				RemoveConstVolatile<RemovedReference>
			>
		>;
	};
	template<typename T> using Decay = typename DecayPrivate<T>::Type;
	
	template<typename Base, typename Derived>
	struct IsBaseOfPrivate
	{
		static constexpr bool Test(const Base*) { return true ; }
		static constexpr bool Test(...)         { return false; }
		static constexpr bool Value = Test(static_cast<Derived*>(nullptr));
	};
	template<typename Base, typename Derived> inline constexpr bool IsBaseOf = IsBaseOfPrivate<Base, Derived>::Value;
	
	template<typename T, typename = void> struct IsDefinedPrivate             : FalseType {};
	template<typename T>                  struct IsDefinedPrivate<T, Void<T>> : TrueType  {};
	template<typename T> inline constexpr bool IsDefined = IsDefinedPrivate<Decay<T>>::Value;
	
	template<typename T> constexpr RemoveReference<T>&& Move(T&& InValue) noexcept { return static_cast<Meta::RemoveReference<T>&&>(InValue); }
	
	template<typename T> constexpr T&& Forward(RemoveReference<T>&  InValue) noexcept { return static_cast<T&&>(InValue); }
	template<typename T> constexpr T&& Forward(RemoveReference<T>&& InValue) noexcept
	{
		static_assert(IsRValueReference<T>, "Cannot forward rvalue as lvalue!");
		return static_cast<T&&>(InValue);
	}
	
	template<typename T>
	constexpr void Swap(T& A, T& B) noexcept
	{
		T Temp = Move(A);
		A = Move(B);
		B = Move(Temp);
	}
	
	template<usize... Indices>           struct IndexSequence {};
	template<usize N, usize... Indices> struct MakeIndexSequencePrivate : MakeIndexSequencePrivate<N - 1, N - 1, Indices...> {};
	template<usize... Indices>           struct MakeIndexSequencePrivate<0, Indices...> { using Type = IndexSequence<Indices...>; };
	template<usize N> using MakeIndexSequence = typename MakeIndexSequencePrivate<N>::Type;
	
	template <typename Func, typename Tuple, usize... Indices> constexpr decltype(auto) ApplyPrivate(Func&& InFunc, Tuple&& InTuple, IndexSequence<Indices...>) { return Forward<Func>(InFunc)(InTuple.template Get<Indices>()...); }
	template <typename Func, typename Tuple> constexpr decltype(auto) Apply(Func&& InFunc, Tuple&& InTuple) { return ApplyPrivate(Forward<Func>(InFunc), Forward<Tuple>(InTuple), MakeIndexSequence<RemoveReference<Tuple>::Size>{} ); }
	
	template <typename T, typename Func, typename = void> struct HasMember                                                          : FalseType {};
	template <typename T, typename Func>                  struct HasMember<T, Func, Void<decltype(DeclVal<Func>()(DeclVal<T&>()))>> : TrueType  {};
	
	template <typename T, typename = void> struct IsContainerPrivate                                                : FalseType {};
	template <typename T>                  struct IsContainerPrivate<T, Void<decltype(DeclVal<T&>().ChildWidgets)>> : TrueType  {};
	template <typename T> inline constexpr bool IsContainer = IsContainerPrivate<Decay<T>>::Value;
	
	template<typename T> using EnableIfWrapper   = EnableIf<!IsContainer<T>, T>;
	template<typename T> using EnableIfContainer = EnableIf< IsContainer<T>, T>;
}
