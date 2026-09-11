// Root Engine / Basement

#include "Vector2D.h"
#include "Math.h"

float FVector2D::Length() const
{
    return FMath::Sqrt(X*X + Y*Y);
}

FVector2D FVector2D::GetSafeNormal() const
{
    float len = Length();
    if (len > 1e-6f) return *this * (1.0f / len);
    return FVector2D(0);
}

constexpr FVector2D FVector2D::UpVector    = FVector2D(0.f, 1.f);
constexpr FVector2D FVector2D::RightVector = FVector2D(1.f, 0.f);
constexpr FVector2D FVector2D::DownVector  = FVector2D(0.f, -1.f);
constexpr FVector2D FVector2D::LeftVector  = FVector2D(-1.f, 0.f);
