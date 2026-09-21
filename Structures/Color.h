// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "../Math/Math.h"

struct FLinearColor;

struct FColor
{
	
public:
	uint8 R;
	uint8 G;
	uint8 B;
	uint8 A;
	
    constexpr FColor() = default;
    explicit constexpr FColor(const uint8 InRGB, const uint8 InA = 255) : R(InRGB), G(InRGB), B(InRGB), A(InA) {}
	explicit constexpr FColor(const uint8 InR, const uint8 InG, const uint8 InB, const uint8 InA = 255) : R(InR), G(InG), B(InB), A(InA) {}
	explicit constexpr FColor(const FLinearColor& InLinearColor);
	
	constexpr FLinearColor ToLinearColor() const;
	
	constexpr FColor operator+(const FColor& InOther) const 
    {
    	return FColor(
			FMath::Clamp(static_cast<int32>(R) + InOther.R, 0, 255),
			FMath::Clamp(static_cast<int32>(G) + InOther.G, 0, 255),
			FMath::Clamp(static_cast<int32>(B) + InOther.B, 0, 255),
			A
		);
	}
	constexpr FColor operator-(const FColor& InOther) const 
    {
    	return FColor(
			FMath::Clamp(static_cast<int32>(R) - InOther.R, 0, 255),
			FMath::Clamp(static_cast<int32>(G) - InOther.G, 0, 255),
			FMath::Clamp(static_cast<int32>(B) - InOther.B, 0, 255),
			A
		);
	}
	
	constexpr FColor operator*(const FColor& InOther) const 
	{
    	return FColor(
			static_cast<uint8>((static_cast<int32>(R) * InOther.R) >> 8),
			static_cast<uint8>((static_cast<int32>(G) * InOther.G) >> 8),
			static_cast<uint8>((static_cast<int32>(B) * InOther.B) >> 8),
			A
		);
	}
	
	constexpr FColor operator/(const FColor& InOther) const 
	{
    	return FColor(
			InOther.R == 0 ? 255 : FMath::Clamp(static_cast<int32>(static_cast<float>(R) / static_cast<float>(InOther.R) * 255.f), 0, 255),
			InOther.G == 0 ? 255 : FMath::Clamp(static_cast<int32>(static_cast<float>(G) / static_cast<float>(InOther.G) * 255.f), 0, 255),
			InOther.B == 0 ? 255 : FMath::Clamp(static_cast<int32>(static_cast<float>(B) / static_cast<float>(InOther.B) * 255.f), 0, 255),
			A
		); 
	}
	
	constexpr FColor operator*(const float InScalar) const
    {
    	return FColor(
			static_cast<uint8>(FMath::Clamp(static_cast<int32>(static_cast<float>(R) * InScalar), 0, 255)),
			static_cast<uint8>(FMath::Clamp(static_cast<int32>(static_cast<float>(G) * InScalar), 0, 255)),
			static_cast<uint8>(FMath::Clamp(static_cast<int32>(static_cast<float>(B) * InScalar), 0, 255)),
			A
		);
    }
	
	constexpr FColor operator/(const float InScalar) const 
    { 
    	return FColor(
			static_cast<uint8>(FMath::Clamp(static_cast<int32>(static_cast<float>(R) / InScalar), 0, 255)),
			static_cast<uint8>(FMath::Clamp(static_cast<int32>(static_cast<float>(G) / InScalar), 0, 255)),
			static_cast<uint8>(FMath::Clamp(static_cast<int32>(static_cast<float>(B) / InScalar), 0, 255)),
			A
		);
    }
	
	constexpr FColor& operator+=(const FColor& InOther) { *this = *this + InOther; return *this; }
	constexpr FColor& operator-=(const FColor& InOther) { *this = *this - InOther; return *this; }
	constexpr FColor& operator*=(const FColor& InOther) { *this = *this * InOther; return *this; }
	constexpr FColor& operator/=(const FColor& InOther) { *this = *this / InOther; return *this; }
	
	constexpr FColor& operator*=(const float InScalar) { *this = *this * InScalar; return *this; }
	constexpr FColor& operator/=(const float InScalar) { *this = *this / InScalar; return *this; }
	
	static const FColor Black;
    static const FColor White;
    static const FColor Gray;
    static const FColor Silver;
	
    static const FColor Red;
    static const FColor Green;
    static const FColor Blue;
	
    static const FColor Yellow;
    static const FColor Cyan;
    static const FColor Magenta;
	
    static const FColor Orange;
    static const FColor Purple;
    static const FColor Turquoise;
};

inline constexpr FColor FColor::Black     = FColor(0  , 0  , 0  );
inline constexpr FColor FColor::White     = FColor(255, 255, 255);
inline constexpr FColor FColor::Gray      = FColor(128, 128, 128);
inline constexpr FColor FColor::Silver    = FColor(192, 192, 192);

inline constexpr FColor FColor::Red       = FColor(255, 0  , 0  );
inline constexpr FColor FColor::Green     = FColor(0  , 255, 0  );
inline constexpr FColor FColor::Blue      = FColor(0  , 0  , 255);

inline constexpr FColor FColor::Yellow    = FColor(255, 255, 0  );
inline constexpr FColor FColor::Cyan      = FColor(0  , 255, 255);
inline constexpr FColor FColor::Magenta   = FColor(255, 0  , 255);

inline constexpr FColor FColor::Orange    = FColor(255, 128, 0  );
inline constexpr FColor FColor::Purple    = FColor(128, 0  , 128);
inline constexpr FColor FColor::Turquoise = FColor(64 , 224, 208);
