// Root Engine / Basement

#pragma once

#include <array>
#include <string>

#include "Vector4D.h"

/** Стандартная Матрица 4 на 4 */
struct FMatrix4x4
{
    FVector4D Rows[4] =
    {
        FVector4D(1.f, 0.f, 0.f, 0.f),
        FVector4D(0.f, 1.f, 0.f, 0.f),
        FVector4D(0.f, 0.f, 1.f, 0.f),
        FVector4D(0.f, 0.f, 0.f, 1.f)
    };
    
    explicit constexpr FMatrix4x4() : FMatrix4x4(1.f) {}
    
    explicit constexpr FMatrix4x4(const float DiagonalValue)
    {
        Rows[0] = FVector4D(DiagonalValue, 0, 0, 0);
        Rows[1] = FVector4D(0, DiagonalValue, 0, 0);
        Rows[2] = FVector4D(0, 0, DiagonalValue, 0);
        Rows[3] = FVector4D(0, 0, 0, DiagonalValue);
    }

    explicit constexpr FMatrix4x4(const FVector4D& InA, const FVector4D& InB, const FVector4D& InC, const FVector4D& InD)
    {
        Rows[0] = InA;
        Rows[1] = InB;
        Rows[2] = InC;
        Rows[3] = InD;
    }
    
    explicit constexpr FMatrix4x4
    (
        const float AA, const float AB, const float AC, const float AD,
        const float BA, const float BB, const float BC, const float BD,
        const float CA, const float CB, const float CC, const float CD,
        const float DA, const float DB, const float DC, const float DD
    )
    {
        Rows[0] = FVector4D(AA, AB, AC, AD);
        Rows[1] = FVector4D(BA, BB, BC, BD);
        Rows[2] = FVector4D(CA, CB, CC, CD);
        Rows[3] = FVector4D(DA, DB, DC, DD);
    }
    
    static FMatrix4x4 CreateScale(const FVector3D& Scale);
    static FMatrix4x4 CreateTranslation(const FVector3D& Translation);
    
    static FMatrix4x4 CreatePerspective(float FOVDegrees, float AspectRatio, float NearPlane, float FarPlane);
    static FMatrix4x4 CreateOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane);
    // static FMatrix4x4 CreateViewMatrixOptimized(const FVector3D& Location, const FQuat& Quat);

    static FMatrix4x4 LookAt(const FVector3D& Eye, const FVector3D& Center, const FVector3D& Up);

    
    FMatrix4x4 operator*(const FMatrix4x4& Other) const {
        const FVector4D& A0 = Rows[0];
        const FVector4D& A1 = Rows[1];
        const FVector4D& A2 = Rows[2];
        const FVector4D& A3 = Rows[3];

        const FVector4D& B0 = FVector4D(Other.Rows[0][0], Other.Rows[1][0], Other.Rows[2][0], Other.Rows[3][0]);
        const FVector4D& B1 = FVector4D(Other.Rows[0][1], Other.Rows[1][1], Other.Rows[2][1], Other.Rows[3][1]);
        const FVector4D& B2 = FVector4D(Other.Rows[0][2], Other.Rows[1][2], Other.Rows[2][2], Other.Rows[3][2]);
        const FVector4D& B3 = FVector4D(Other.Rows[0][3], Other.Rows[1][3], Other.Rows[2][3], Other.Rows[3][3]);

        return FMatrix4x4(
            FVector4D(A0.Dot(B0), A0.Dot(B1), A0.Dot(B2), A0.Dot(B3)),
            FVector4D(A1.Dot(B0), A1.Dot(B1), A1.Dot(B2), A1.Dot(B3)),
            FVector4D(A2.Dot(B0), A2.Dot(B1), A2.Dot(B2), A2.Dot(B3)),
            FVector4D(A3.Dot(B0), A3.Dot(B1), A3.Dot(B2), A3.Dot(B3))
        );
    }

    FVector3D TransformVector(const FVector3D& V) const;
    FVector3D TransformPosition(const FVector3D& V) const;
    std::string ToString() const;

    std::array<float,16> ToGLMatrix() const;

    static const FMatrix4x4 Identity;
    static const FMatrix4x4 Diagonal;
};

inline constexpr FMatrix4x4 FMatrix4x4::Identity = FMatrix4x4(1.f);
inline constexpr FMatrix4x4 FMatrix4x4::Diagonal = FMatrix4x4
(
    FVector4D(1.f, 0.f, 0.f, 0.f),
    FVector4D(0.f, 1.f, 0.f, 0.f),
    FVector4D(0.f, 0.f, 1.f, 0.f),
    FVector4D(0.f, 0.f, 0.f, 1.f)
);
