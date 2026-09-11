// Root Engine / Basement

#pragma once

struct FMathConstants
{
	
public:
	static constexpr float Pi       = 3.14159265358979323846f;
	static constexpr float TwoPi    = 2.f * Pi;
	static constexpr float HalfPi   = Pi * 0.5f;
	static constexpr float DegToRad = Pi / 180.f;
	static constexpr float RadToDeg = 180.f / Pi;
	
	static constexpr float Epsilon  = 1e-6f;
	
	static constexpr float MaxFloat = 3.402823466e+38F;
	static constexpr float MinFloat = 1.175494351e-38F;
};
