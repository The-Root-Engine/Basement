// Root Engine / Basement

#pragma once

#include "MathConstants.h"

struct FMath
{
    
public:
    template<typename T> static T Min(const T InA, const T InB) { return InA < InB ? InA : InB; }
    template<typename T> static T Max(const T InA, const T InB) { return InA > InB ? InA : InB; }
    template<typename T> static T Min3(const T InA, const T InB, const T InC) { return Min(Min(InA, InB), InC); }
    template<typename T> static T Max3(const T InA, const T InB, const T InC) { return Max(Max(InA, InB), InC); }
    template<typename T> static T Clamp(const T InValue, const T InMin, const T InMax) { return Min(Max(InValue, InMin), InMax); }
    template<typename T> static T Abs(const T InF) { return InF < 0 ? -InF : InF; }
    
	template<typename T, typename U> 
	static T Lerp(const T InA, const T InB, const U InAlpha) { return T(U(InA) + U(InB - InA) * InAlpha); }
	
    static bool IsNearlyZero(const float InF, const float InTolerance = FMathConstants::Epsilon) { return (InF > -InTolerance) && (InF < InTolerance); }
    static bool IsNearlyEqual(const float InA, const float InB, const float InTolerance = FMathConstants::Epsilon) { return IsNearlyZero(InA - InB, InTolerance); }
	
    static float Sqrt(const float InF);
    static float Floor(const float InF);
	
    static float Sin(const float InRadians);
    static float Cos(const float InRadians);
    static float Tan(const float InRadians);
    static float Asin(const float InF);
    static float Acos(const float InF);
    static float Atan2(const float InY, const float InX);
	
    static constexpr float RadiansToDegrees(const float InRadians) { return InRadians * FMathConstants::RadToDeg; }
    static constexpr float DegreesToRadians(const float InDegrees) { return InDegrees * FMathConstants::DegToRad; }
};
