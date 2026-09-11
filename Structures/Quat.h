// Root Engine / Basement

#pragma once

#include "Matrix4x4.h"

struct FMatrix4x4;
struct FVector3D;
struct FRotator;
struct FRotator;

struct FQuat 
{
    float X, Y, Z, W;

    explicit FQuat() : X(0.f), Y(0.f), Z(0.f), W(1.f) {}
    explicit FQuat(float InX, float InY, float InZ, float InW) : X(InX), Y(InY), Z(InZ), W(InW) {}

    FVector3D RotateVector(const FVector3D& V) const;
    
    FVector3D GetForward() const;
    FVector3D GetRight() const;
    FVector3D GetUp() const;
    
    FQuat operator*(const FQuat& Q) const {
        return FQuat(
            W * Q.X + X * Q.W + Y * Q.Z - Z * Q.Y,
            W * Q.Y - X * Q.Z + Y * Q.W + Z * Q.X,
            W * Q.Z + X * Q.Y - Y * Q.X + Z * Q.W,
            W * Q.W - X * Q.X - Y * Q.Y - Z * Q.Z
        );
    }

    static FQuat FromAxisAngle(const FVector3D& Axis, float AngleRad);
    
    FRotator ToRotator() const;
    
    FMatrix4x4 ToMatrix4x4() const;

    static constexpr FQuat Identity;
};
