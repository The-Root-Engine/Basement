// Root Engine / Basement

#pragma once

template<typename T1, typename T2>
struct TPair
{
    
public:
    T1 First;
    T2 Second;
    
    TPair(const T1& InFirst, const T2& InSecond) : First(InFirst), Second(InSecond) {}
};
