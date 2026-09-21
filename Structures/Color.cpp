// Root Engine / Basement

#include "Color.h"

#include "LinearColor.h"

constexpr FColor::FColor(const FLinearColor& InLinearColor)
	: R(static_cast<uint8>(FMath::Clamp(InLinearColor.R * 255.f, 0.f, 255.f)))
	, G(static_cast<uint8>(FMath::Clamp(InLinearColor.G * 255.f, 0.f, 255.f)))
	, B(static_cast<uint8>(FMath::Clamp(InLinearColor.B * 255.f, 0.f, 255.f)))
	, A(static_cast<uint8>(FMath::Clamp(InLinearColor.A * 255.f, 0.f, 255.f)))
{
	
}

constexpr FLinearColor FColor::ToLinearColor() const
{
	return FLinearColor(
		static_cast<float>(R) / 255.f,
		static_cast<float>(G) / 255.f,
		static_cast<float>(B) / 255.f,
		static_cast<float>(A) / 255.f
	);
}
