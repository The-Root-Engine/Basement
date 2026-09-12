// Root Engine / Basement

#pragma once

#include "Meta.h"

template<typename T>
constexpr void Swap(T& A, T& B) noexcept { Meta::Swap(A, B); }

template<typename T> constexpr Meta::RemoveReference<T>&& Move(T&& InValue) noexcept { return Meta::Move(InValue); }

template<typename T> constexpr T&& Forward(Meta::RemoveReference<T>&  InValue) noexcept { return Meta::Forward<T>(InValue); }
template<typename T> constexpr T&& Forward(Meta::RemoveReference<T>&& InValue) noexcept { return Meta::Forward<T>(InValue); }
