// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"

template<typename T, uint32 N>
struct TStaticArray
{
	
public:
	constexpr TStaticArray() = default;
	
	template<typename... Args>
	constexpr TStaticArray(Args&&... InArgs) : DataRaw{ T(InArgs)... }
	{
		static_assert(sizeof...(Args) == N, "TStaticArray: Wrong number of elements!");
	}
	
	/* */ T& operator[](const uint32 InIndex) /* */ { return DataRaw[InIndex]; }
	const T& operator[](const uint32 InIndex) const { return DataRaw[InIndex]; }
    
	/* */ T* Data() /* */ { return DataRaw; }
	const T* Data() const { return DataRaw; }
    
	/* */ T* First() /* */ { return DataRaw[0]; }
	const T* First() const { return DataRaw[0]; }
    
	/* */ T* Last() /* */  { return DataRaw[N - 1]; }
	const T* Last() const  { return DataRaw[N - 1]; }
	
	static constexpr uint32 Num() { return N; }
	
	T* begin() { return DataRaw; }
	T* end()   { return DataRaw + N; }
    
	const T* begin() const noexcept { return DataRaw; }
	const T* end()   const noexcept { return DataRaw + N; }
    
	const T* cbegin() const noexcept { return DataRaw; }
	const T* cend()   const noexcept { return DataRaw + N; }

private:
	T DataRaw[N];
};
