// Root Engine / Basement

#include "LinearColor.h"

#include "Color.h"

constexpr FLinearColor::FLinearColor(const FColor& InColor)
	: R(static_cast<float>(InColor.R) / 255.f)
	, G(static_cast<float>(InColor.G) / 255.f)
	, B(static_cast<float>(InColor.B) / 255.f)
	, A(static_cast<float>(InColor.A) / 255.f)
{
	
}

constexpr FColor FLinearColor::ToColor() const
{
	return FColor(
		static_cast<uint8>(FMath::Clamp(R * 255.f, 0.f, 255.f)),
		static_cast<uint8>(FMath::Clamp(G * 255.f, 0.f, 255.f)),
		static_cast<uint8>(FMath::Clamp(B * 255.f, 0.f, 255.f)),
		static_cast<uint8>(FMath::Clamp(A * 255.f, 0.f, 255.f))
	);
}
