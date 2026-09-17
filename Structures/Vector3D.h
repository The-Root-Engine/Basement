// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "../Containers/String.h"
#include "Vector2D.h"

struct FVector3D 
{
    float X, Y, Z;

    explicit constexpr FVector3D()                                       : X(0), Y(0), Z(0) {}
    explicit constexpr FVector3D(float InXYZ)                            : X(InXYZ), Y(InXYZ), Z(InXYZ) {}
    explicit constexpr FVector3D(float InX, float InY)                   : X(InX), Y(InY), Z(0) {}
    explicit constexpr FVector3D(const FVector2D& InXY)                  : X(InXY.X), Y(InXY.Y), Z(0) {}
    explicit constexpr FVector3D(float InX, float InY, float InZ)        : X(InX), Y(InY), Z(InZ) {}
    
    FVector3D operator+(const FVector3D& Other) const { return FVector3D(X + Other.X, Y + Other.Y, Z + Other.Z); }
    FVector3D operator-(const FVector3D& Other) const { return FVector3D(X - Other.X, Y - Other.Y, Z - Other.Z); }
    FVector3D operator*(const FVector3D& Other) const { return FVector3D(X * Other.X, Y * Other.Y, Z * Other.Z); }
    FVector3D operator*(float Scalar)           const { return FVector3D(X * Scalar, Y * Scalar, Z * Scalar); }
    FVector3D operator/(float Scalar)           const { return FVector3D(X / Scalar, Y / Scalar, Z / Scalar); }
    FVector3D operator-()                       const { return FVector3D(-X, -Y, -Z); }

    FVector2D XY() const { return FVector2D(X, Y); }
    FVector2D YX() const { return FVector2D(Y, X); }
    FVector2D XZ() const { return FVector2D(X, Z); }
    FVector2D ZX() const { return FVector2D(Z, X); }
    FVector2D YZ() const { return FVector2D(Y, Z); }
    FVector2D ZY() const { return FVector2D(Z, Y); }
    
    float LengthSquared() const { return X*X + Y*Y + Z*Z; }
    float Length() const;
    
    static FVector3D Normalize(const FVector3D& V);
    static FVector3D Cross(const FVector3D& A, const FVector3D& B);
    
    FVector3D GetSafeNormal() const { float len = Length(); return (len > 1e-6f) ? *this * (1.0f / len) : FVector3D{0}; }
    static float Dot(const FVector3D& A, const FVector3D& B);
    
    FString ToString() const;
    
    static const FVector3D ForwardVector;
    static const FVector3D RightVector;
    static const FVector3D UpVector;
    static const FVector3D BackwardVector;
    static const FVector3D LeftVector;
    static const FVector3D DownVector;
    static const FVector3D ZeroVector;
    static const FVector3D OneVector;
};

inline constexpr FVector3D FVector3D::ForwardVector   = FVector3D( 1.f,  0.f,  0.f);
inline constexpr FVector3D FVector3D::RightVector     = FVector3D( 0.f,  1.f,  0.f);
inline constexpr FVector3D FVector3D::UpVector        = FVector3D( 0.f,  0.f,  1.f);
inline constexpr FVector3D FVector3D::BackwardVector  = FVector3D(-1.f,  0.f,  0.f);
inline constexpr FVector3D FVector3D::LeftVector      = FVector3D( 0.f, -1.f,  0.f);
inline constexpr FVector3D FVector3D::DownVector      = FVector3D( 0.f,  0.f, -1.f);
inline constexpr FVector3D FVector3D::ZeroVector      = FVector3D( 0.f,  0.f,  0.f);
inline constexpr FVector3D FVector3D::OneVector       = FVector3D( 1.f,  1.f,  1.f);
