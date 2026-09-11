// Root Engine / Basement

#pragma once

struct FMathGeometry
{
    
public:
	template<typename T>
    static bool IsLineSegmentsIntersect(const T A, const T B, const T C, const T D)
    {
        const T::ScalarType Denominator = (B.X - A.X) * (D.Y - C.Y) - (B.Y - A.Y) * (D.X - C.X);
        if(Denominator == T::ScalarType(0)) return false;
        
        const T::ScalarType U = ((C.X - A.X) * (D.Y - C.Y) - (C.Y - A.Y) * (D.X - C.X)) / Denominator;
        const T::ScalarType I = ((C.X - A.X) * (B.Y - A.Y) - (C.Y - A.Y) * (B.X - A.X)) / Denominator;
        
        return U >= T::ScalarType(0) && U <= T::ScalarType(1) && I >= T::ScalarType(0) && I <= T::ScalarType(1);
    }
};
