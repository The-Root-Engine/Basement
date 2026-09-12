// Root Engine / Basement

#include "Vector3D.h"

#include <iomanip>
#include <sstream>

#include "../Math/Math.h"

float FVector3D::Length() const
{
    return FMath::Sqrt(X*X + Y*Y);
}

FVector3D FVector3D::Normalize(const FVector3D& V)
{
    const float Len = FMath::Sqrt(V.X*V.X + V.Y*V.Y + V.Z*V.Z);
    return FVector3D(V.X/Len, V.Y/Len, V.Z/Len);
}

float FVector3D::Dot(const FVector3D& A, const FVector3D& B)
{
    return A.X * B.X + A.Y*B.Y + A.Z*B.Z;
}

FVector3D FVector3D::Cross(const FVector3D& A, const FVector3D& B)
{
    return FVector3D(
        A.Y * B.Z - A.Z * B.Y,
        A.Z * B.X - A.X * B.Z,
        A.X * B.Y - A.Y * B.X
    );
}

std::string FVector3D::ToString() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);

    ss << "(X = " << std::setw(5) << X
      << ", Y = " << std::setw(5) << Y
      << ", Z = " << std::setw(5) << Z
      << ")";

    return ss.str();
}
