// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "Vector2D.h"
#include "Vector3D.h"

struct FVector4D 
{
    float X, Y, Z, W;
    
    explicit constexpr FVector4D()                                               : X(0), Y(0), Z(0), W(0) {}
    explicit constexpr FVector4D(float InXYZW)                                   : X(InXYZW), Y(InXYZW), Z(InXYZW), W(InXYZW) {}
    explicit constexpr FVector4D(const FVector3D& InXYZ)                         : X(InXYZ.X), Y(InXYZ.Y), Z(InXYZ.Z), W(0) {}
    explicit constexpr FVector4D(const FVector3D& InXYZ, float InW)              : X(InXYZ.X), Y(InXYZ.Y), Z(InXYZ.Z), W(InW) {}
    explicit constexpr FVector4D(const FVector2D& AInXY, const FVector2D& BInXY) : X(AInXY.X), Y(AInXY.Y), Z(BInXY.X), W(BInXY.Y) {}
    explicit constexpr FVector4D(float InX, float InY, float InZ, float InW)     : X(InX), Y(InY), Z(InZ), W(InW) {}
    //explicit FVector4D(const FQuat& InQuat)                            : X(InQuat.X), Y(InQuat.Y), Z(InQuat.Z), W(InQuat.W) {}

    FVector4D operator+(const FVector4D& Other) const { return FVector4D(X + Other.X, Y + Other.Y, Z + Other.Z, W + Other.W); }
    FVector4D operator-(const FVector4D& Other) const { return FVector4D(X - Other.X, Y - Other.Y, Z - Other.Z, W - Other.W); }
    FVector4D operator*(const FVector4D& Other) const { return FVector4D(X * Other.X, Y * Other.Y, Z * Other.Z, W * Other.W); }
    FVector4D operator*(float Scalar) const { return FVector4D(X * Scalar, Y * Scalar, Z * Scalar, W * Scalar); }
    FVector4D operator/(float Scalar) const { float Inv = 1.0f / Scalar; return FVector4D(X / Inv, Y * Inv, Z * Inv, W * Inv); }
    
    FVector4D& operator+=(const FVector4D& Other) { X += Other.X; Y += Other.Y; Z += Other.Z; W += Other.W; return *this; }
    FVector4D& operator-=(const FVector4D& Other) { X -= Other.X; Y -= Other.Y; Z -= Other.Z; W -= Other.W; return *this; }
    FVector4D& operator*=(float Scalar) { X *= Scalar; Y *= Scalar; Z *= Scalar; W *= Scalar; return *this; }
    FVector4D& operator/=(float Scalar) { float Inv = 1.0f / Scalar; X *= Inv; Y *= Inv; Z *= Inv; W *= Inv; return *this; }
    
    float LengthSquared() const { return X*X + Y*Y + Z*Z + W*W; }
    float Length() const;

    FVector4D GetSafeNormal() const { float len = Length(); return (len > 1e-6f) ? *this * (1.0f / len) : FVector4D{0}; }
    float Dot(const FVector4D& Other) const { return X * Other.X + Y * Other.Y + Z * Other.Z + W * Other.W; }

    FVector3D XYZ() const { return FVector3D(X, Y, Z); }
    FVector3D ToVector3D() const { return W == 0.f ? XYZ() : XYZ() / W; }

    bool IsZero() const;

    bool operator==(const FVector4D& Other) const;
    bool operator!=(const FVector4D& Other) const { return !(*this == Other); }
    
    float operator[](const uint8 InIndex) const
	{
        switch(InIndex) 
		{
		default:
        case 0:  return X;
        case 1:  return Y;
        case 2:  return Z;
        case 3:  return W;
        }
    }
	
    float& operator[](const uint8 InIndex)
	{
        switch(InIndex) 
		{
		default:
        case 0:  return X;
        case 1:  return Y;
        case 2:  return Z;
        case 3:  return W;
        }
    }
	
    static const FVector4D ZeroVector;
    static const FVector4D OneVector;
};

inline constexpr FVector4D FVector4D::ZeroVector = FVector4D(0.f);
inline constexpr FVector4D FVector4D::OneVector  = FVector4D(1.f);
