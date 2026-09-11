// Root Engine / Basement

#pragma once

#include "Matrix4x4.h"
#include "Vector3D.h"
#include "Quat.h"

struct FTransform 
{
    FVector3D Location = FVector3D::ZeroVector;
    FQuat Rotation = FQuat::Identity;
    FVector3D Scale = FVector3D::OneVector;

    explicit FTransform(const FVector3D& InLocation) : Location(InLocation) {}
    explicit FTransform(const FVector3D& InLocation, const FQuat& InRotation, const FVector3D& InScale) : Location(InLocation), Rotation(InRotation), Scale(InScale) {}

    FMatrix4x4 ToMatrix() const { return FMatrix4x4::CreateTranslation(Location) * Rotation.ToMatrix4x4() * FMatrix4x4::CreateScale(Scale); }

    FVector3D TransformPosition(const FVector3D& V) const { return ToMatrix().TransformPosition(V); }
    
    FTransform Combine(const FTransform& Other) const { return FTransform(TransformPosition(Other.Location), Rotation * Other.Rotation, Scale * Other.Scale); }
};
