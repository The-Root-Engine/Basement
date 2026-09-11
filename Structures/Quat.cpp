// Root Engine / Basement

#include "Quat.h"
#include "Math.h"
#include "Rotator.h"
#include "Vector3D.h"

FVector3D FQuat::RotateVector(const FVector3D& V) const
{
    /*float Xr = W * V.X + Y * V.Z - Z * V.Y;
    float Yr = W * V.Y - X * V.Z + Z * V.X;
    float Zr = W * V.Z + X * V.Y - Y * V.X;
    float Wr = -(X * V.X + Y * V.Y + Z * V.Z);

    return FVector3D(
        -Wr * X + Xr * W - Yr * Z + Zr * Y,
        -Wr * Y + Xr * Z + Yr * W - Zr * X,
        -Wr * Z - Xr * Y + Yr * X + Zr * W);*/

    FVector3D qVec(X, Y, Z);
    FVector3D uv = FVector3D::Cross(qVec, V);
    FVector3D uuv = FVector3D::Cross(qVec, uv);
    return V + (uv * W + uuv) * 2.0f;
}

FVector3D FQuat::GetForward() const
{
    return RotateVector(FVector3D(0, 0, 1));
}

FVector3D FQuat::GetRight() const
{
    return RotateVector(FVector3D(1,0,0));
}

FVector3D FQuat::GetUp() const
{
    return RotateVector(FVector3D(0,1,0));
}

FQuat FQuat::FromAxisAngle(const FVector3D& Axis, float AngleRad)
{
    FVector3D NormAxis = Axis.GetSafeNormal();
    float HalfAngle = AngleRad * 0.5f;
    float Sin = FMath::Sin(HalfAngle);
    
    return FQuat(
        NormAxis.X * Sin,
        NormAxis.Y * Sin,
        NormAxis.Z * Sin,
        FMath::Cos(HalfAngle)
    );
}

inline FRotator FQuat::ToRotator() const
{
    const float& Y_Square = Y * Y;
    return FRotator(
        FMath::RadiansToDegrees(FMath::Asin(2.f * (W * Y - Z * X))),
        FMath::RadiansToDegrees(FMath::Atan2(  2.f * (W * Z + X * Y), 1.f - 2.f * (Y_Square + Z * Z))),
        FMath::RadiansToDegrees(FMath::Atan2(  2.f * (W * X + Y * Z), 1.f - 2.f * (X * X + Y_Square)))
    );
}

FMatrix4x4 FQuat::ToMatrix4x4() const
{
    float xx = X * X;
    float yy = Y * Y;
    float zz = Z * Z;
    float xy = X * Y;
    float xz = X * Z;
    float yz = Y * Z;
    float wx = W * X;
    float wy = W * Y;
    float wz = W * Z;

    return FMatrix4x4(
        1.f - 2.f * (yy + zz), 2.f * (xy - wz),       2.f * (xz + wy),       0.f,
        2.f * (xy + wz),       1.f - 2.f * (xx + zz), 2.f * (yz - wx),       0.f,
        2.f * (xz - wy),       2.f * (yz + wx),       1.f - 2.f * (xx + yy), 0.f,
        0.f,                   0.f,                   0.f,                   1.f
    );
}

const FQuat FQuat::Identity = FQuat(0, 0, 0, 1);
