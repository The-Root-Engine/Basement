// Root Engine / Basement

#pragma once

#include "../Structures/Vector2D.h"

struct FMathGeometry
{
    
public:
	template<typename T>
	static constexpr T DistanceSquared(const TVector2D<T>& InF)
	{
		return (InF.X * InF.X) + (InF.Y * InF.Y);
	}
	
	template<typename T>
	static T Distance(const TVector2D<T>& InF)
	{
		return FMath::Sqrt(DistanceSquared(InF));
	}
	
	template<typename T>
	static constexpr T DistanceSquared(const TVector2D<T>& InA, const TVector2D<T>& InB)
	{
		return DistanceSquared(InA - InB);
	}
	
	template<typename T>
	static T Distance(const TVector2D<T>& InA, const TVector2D<T>& InB)
	{
		return FMath::Sqrt(DistanceSquared(InA, InB));
	}
	
	template<typename T>
	static constexpr T Dot(const TVector2D<T>& InA, const TVector2D<T>& InB)
	{
		return (InA.X * InB.X) + (InA.Y * InB.Y);
	}
	
	template<typename T>
    static bool IsLineSegmentsIntersect(const TVector2D<T>& InA, const TVector2D<T>& InB, const TVector2D<T>& InC, const TVector2D<T>& InD)
    {
        const T Denominator = (InB.X - InA.X) * (InD.Y - InC.Y) - (InB.Y - InA.Y) * (InD.X - InC.X);
		if(FMath::IsNearlyZero(Denominator)) return false;
        
        const T U = ((InC.X - InA.X) * (InD.Y - InC.Y) - (InC.Y - InA.Y) * (InD.X - InC.X)) / Denominator;
        const T I = ((InC.X - InA.X) * (InB.Y - InA.Y) - (InC.Y - InA.Y) * (InB.X - InA.X)) / Denominator;
        
        return U >= T(0) && U <= T(1) && I >= T(0) && I <= T(1);
    }
	
	template<typename T>
	static T DistancePointToSegment(const TVector2D<T>& InP, const TVector2D<T>& InA, const TVector2D<T>& InB)
	{
		const TVector2D<T> AB = InB - InA;
		const TVector2D<T> AP = InP - InA;
		
		const T LengthSquared = DistanceSquared(AB);
		if(FMath::IsNearlyZero(LengthSquared)) return Distance(InP, InA);
		
		const T DotProduct = Dot(AP, AB);
		const T Param = FMath::Clamp(DotProduct / LengthSquared, T(0), T(1));
		
		return FMathGeometry::Distance(InP, InA + AB * Param);
	}
};
