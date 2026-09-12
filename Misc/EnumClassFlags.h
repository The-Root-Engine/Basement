// Root Engine / Basement
// Credit: Unreal Engine (Epic Games)

#pragma once

#define ENUM_CLASS_FLAGS(Enum) \
	inline           Enum& operator|=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs); } \
	inline           Enum& operator&=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs); } \
	inline           Enum& operator^=(Enum& Lhs, Enum Rhs) { return Lhs = (Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs); } \
	inline constexpr Enum  operator| (Enum  Lhs, Enum Rhs) { return (Enum)((__underlying_type(Enum))Lhs | (__underlying_type(Enum))Rhs); } \
	inline constexpr Enum  operator& (Enum  Lhs, Enum Rhs) { return (Enum)((__underlying_type(Enum))Lhs & (__underlying_type(Enum))Rhs); } \
	inline constexpr Enum  operator^ (Enum  Lhs, Enum Rhs) { return (Enum)((__underlying_type(Enum))Lhs ^ (__underlying_type(Enum))Rhs); } \
	inline constexpr bool  operator! (Enum  E)             { return !(__underlying_type(Enum))E; } \
	inline constexpr Enum  operator~ (Enum  E)             { return (Enum)~(__underlying_type(Enum))E; }

template<typename Enum> constexpr bool EnumHasAllFlags(Enum Flags, Enum Contains) { return (static_cast<__underlying_type(Enum)>(Flags) & static_cast<__underlying_type(Enum)>(Contains)) == static_cast<__underlying_type(Enum)>(Contains); }
template<typename Enum> constexpr bool EnumHasAnyFlags(Enum Flags, Enum Contains) { return (static_cast<__underlying_type(Enum)>(Flags) & static_cast<__underlying_type(Enum)>(Contains)) != 0; }

template<typename Enum> void EnumAddFlags(Enum& Flags, Enum FlagsToAdd) { Flags |= FlagsToAdd; }
template<typename Enum> void EnumRemoveFlags(Enum& Flags, Enum FlagsToRemove) { Flags &= ~FlagsToRemove; }
