// Root Engine / Basement

#pragma once

template<typename T, usize N>
struct TStaticArray
{
	
public:
	constexpr TStaticArray() = default;
	
	template<typename... Args>
	constexpr TStaticArray(Args&&... InArgs) : Data{T(InArgs)...}
	{
		static_assert(sizeof...(Args) == N, "TStaticArray: Wrong number of elements");
	}
	
	constexpr /* */ T& operator[](size_t InIndex) /* */ { return Data[InIndex]; }
	constexpr const T& operator[](size_t InIndex) const { return Data[InIndex]; }
	
	constexpr /* */ T* Begin() /* */ { return Data; }
	constexpr /* */ T* End()   /* */ { return Data + N; }
	constexpr const T* Begin() const { return Data; }
	constexpr const T* End()   const { return Data + N; }
	
	static constexpr size_t Num() { return N; }
	constexpr void Fill(const T& InValue) { for(size_t i = 0; i < N; ++i) Data[i] = InValue; }

private:
	T Data[N];
};
