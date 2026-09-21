// Root Engine / Basement

#pragma once

#include "MathConstants.h"

template<typename T>
struct TVector2D;

struct FMath
{
    
public:
    template<typename T> static constexpr T Min(const T InA, const T InB) { return InA < InB ? InA : InB; }
    template<typename T> static constexpr T Max(const T InA, const T InB) { return InA > InB ? InA : InB; }
    template<typename T> static constexpr T Min3(const T InA, const T InB, const T InC) { return Min(Min(InA, InB), InC); }
    template<typename T> static constexpr T Max3(const T InA, const T InB, const T InC) { return Max(Max(InA, InB), InC); }
    template<typename T> static constexpr T Clamp(const T InValue, const T InMin, const T InMax) { return Min(Max(InValue, InMin), InMax); }
    template<typename T> static constexpr T Abs(const T InF) { return InF < 0 ? -InF : InF; }
    
	template<typename T, typename U> 
	static constexpr T Lerp(const T InA, const T InB, const U InAlpha) { return T(U(InA) + U(InB - InA) * InAlpha); }
	
    static bool constexpr IsNearlyZero(const float InF, const float InTolerance = FMathConstants::Epsilon) { return (InF > -InTolerance) && (InF < InTolerance); }
    static bool constexpr IsNearlyEqual(const float InA, const float InB, const float InTolerance = FMathConstants::Epsilon) { return IsNearlyZero(InA - InB, InTolerance); }
	
    static float Sqrt(float InF);
    static float Floor(float InF);
    static float Ceil(float InF);
	
    static float Sin(float InRadians);
    static float Cos(float InRadians);
    static float Tan(float InRadians);
    static float Asin(float InF);
    static float Acos(float InF);
    static float Atan2(float InY, float InX);
	
    static constexpr float RadiansToDegrees(const float InRadians) { return InRadians * FMathConstants::RadToDeg; }
    static constexpr float DegreesToRadians(const float InDegrees) { return InDegrees * FMathConstants::DegToRad; }
	
	template<typename T> static constexpr TVector2D<T> Min(const TVector2D<T>& InA, const TVector2D<T>& InB)  { return TVector2D<T>(Min(InA.X, InB.X), Min(InA.Y, InB.Y)); }
	template<typename T> static constexpr TVector2D<T> Max(const TVector2D<T>& InA, const TVector2D<T>& InB)  { return TVector2D<T>(Max(InA.X, InB.X), Max(InA.Y, InB.Y)); }
	template<typename T> static constexpr TVector2D<T> Min3(const TVector2D<T>& InA, const TVector2D<T>& InB, const TVector2D<T>& InC)  { return TVector2D<T>(Min3(InA.X, InB.X, InC.X), Min3(InA.Y, InB.Y, InC.Y)); }
	template<typename T> static constexpr TVector2D<T> Max3(const TVector2D<T>& InA, const TVector2D<T>& InB, const TVector2D<T>& InC)  { return TVector2D<T>(Max3(InA.X, InB.X, InC.X), Max3(InA.Y, InB.Y, InC.Y)); }
	template<typename T> static constexpr TVector2D<T> Clamp(const TVector2D<T>& InValue, const TVector2D<T>& InMin, const TVector2D<T>& InMax)  { return TVector2D<T>(Clamp(InValue.X, InMin.X, InMax.X), Clamp(InValue.Y, InMin.Y, InMax.Y)); }
};
