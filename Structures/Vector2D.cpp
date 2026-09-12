// Root Engine / Basement

#include "Vector2D.h"

#include "../Math/Math.h"

float FVector2D::Length() const
{
    return FMath::Sqrt(X*X + Y*Y);
}

FVector2D FVector2D::GetSafeNormal() const
{
    float len = Length();
    if(len > 1e-6f) return *this * (1.0f / len);
    return FVector2D(0);
}
