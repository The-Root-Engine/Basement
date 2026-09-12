// Root Engine / Basement

#include "Vector4D.h"

#include "../Math/Math.h"

float FVector4D::Length() const
{
    return FMath::Sqrt(LengthSquared());
}

inline bool FVector4D::IsZero() const
{
    return FMath::IsNearlyZero(X) &&
           FMath::IsNearlyZero(Y) &&
           FMath::IsNearlyZero(Z) &&
           FMath::IsNearlyZero(W);
}

inline bool FVector4D::operator==(const FVector4D& Other) const
{
    return FMath::IsNearlyEqual(X, Other.X) &&
           FMath::IsNearlyEqual(Y, Other.Y) &&
           FMath::IsNearlyEqual(Z, Other.Z) &&
           FMath::IsNearlyEqual(W, Other.W);
}
