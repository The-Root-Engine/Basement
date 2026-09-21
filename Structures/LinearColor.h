// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"

struct FColor;

struct FLinearColor
{
	
public:
	float R;
	float G;
	float B;
	float A;
	
    constexpr FLinearColor() = default;
    explicit constexpr FLinearColor(const float InRGB, const float InA = 1.f) : R(InRGB), G(InRGB), B(InRGB), A(InA) {}
	explicit constexpr FLinearColor(const float InR, const float InG, const float InB, const float InA = 1.f) : R(InR), G(InG), B(InB), A(InA) {}
	explicit constexpr FLinearColor(const FColor& InColor);
	
	constexpr FColor ToColor() const;
	
	constexpr FLinearColor operator+(const FLinearColor& InOther) const { return FLinearColor(R + InOther.R, G + InOther.G, B + InOther.B, A + InOther.A); }
	constexpr FLinearColor operator-(const FLinearColor& InOther) const { return FLinearColor(R - InOther.R, G - InOther.G, B - InOther.B, A - InOther.A); }
	constexpr FLinearColor operator*(const FLinearColor& InOther) const { return FLinearColor(R * InOther.R, G * InOther.G, B * InOther.B, A * InOther.A); }
	constexpr FLinearColor operator/(const FLinearColor& InOther) const { return FLinearColor(R / InOther.R, G / InOther.G, B / InOther.B, A / InOther.A); }
	
	constexpr FLinearColor operator*(const float InScalar) const { return FLinearColor(R * InScalar, G * InScalar, B * InScalar, A * InScalar); }
	constexpr FLinearColor operator/(const float InScalar) const { return FLinearColor(R / InScalar, G / InScalar, B / InScalar, A / InScalar); }
	
	constexpr FLinearColor& operator+=(const FLinearColor& InOther) { *this = *this + InOther; return *this; }
	constexpr FLinearColor& operator-=(const FLinearColor& InOther) { *this = *this - InOther; return *this; }
	constexpr FLinearColor& operator*=(const FLinearColor& InOther) { *this = *this * InOther; return *this; }
	constexpr FLinearColor& operator/=(const FLinearColor& InOther) { *this = *this / InOther; return *this; }
	
	constexpr FLinearColor& operator*=(const float InScalar) { *this = *this * InScalar; return *this; }
	constexpr FLinearColor& operator/=(const float InScalar) { *this = *this / InScalar; return *this; }
	
	static const FLinearColor Black;
    static const FLinearColor White;
    static const FLinearColor Gray;
    static const FLinearColor Silver;
	
    static const FLinearColor Red;
    static const FLinearColor Green;
    static const FLinearColor Blue;
	
    static const FLinearColor Yellow;
    static const FLinearColor Cyan;
    static const FLinearColor Magenta;
	
    static const FLinearColor Orange;
    static const FLinearColor Purple;
    static const FLinearColor Turquoise;
};

inline constexpr FLinearColor FLinearColor::Black     = FLinearColor(0.0f,  0.0f,  0.0f );
inline constexpr FLinearColor FLinearColor::White     = FLinearColor(1.0f,  1.0f,  1.0f );
inline constexpr FLinearColor FLinearColor::Gray      = FLinearColor(0.5f,  0.5f,  0.5f );
inline constexpr FLinearColor FLinearColor::Silver    = FLinearColor(0.75f, 0.75f, 0.75f);

inline constexpr FLinearColor FLinearColor::Red       = FLinearColor(1.0f,  0.0f,  0.0f );
inline constexpr FLinearColor FLinearColor::Green     = FLinearColor(0.0f,  1.0f,  0.0f );
inline constexpr FLinearColor FLinearColor::Blue      = FLinearColor(0.0f,  0.0f,  1.0f );

inline constexpr FLinearColor FLinearColor::Yellow    = FLinearColor(1.0f,  1.0f,  0.0f );
inline constexpr FLinearColor FLinearColor::Cyan      = FLinearColor(0.0f,  1.0f,  1.0f );
inline constexpr FLinearColor FLinearColor::Magenta   = FLinearColor(1.0f,  0.0f,  1.0f );

inline constexpr FLinearColor FLinearColor::Orange    = FLinearColor(1.0f,  0.5f,  0.0f );
inline constexpr FLinearColor FLinearColor::Purple    = FLinearColor(0.5f,  0.0f,  0.5f );
inline constexpr FLinearColor FLinearColor::Turquoise = FLinearColor(0.25f, 0.88f, 0.82f);
