// Root Engine / Basement

#include "Matrix4x4.h"

#include <iomanip>
#include <sstream>

#include "Math.h"
#include "Quat.h"

inline FMatrix4x4 FMatrix4x4::CreateScale(const FVector3D& Scale)
{
    return FMatrix4x4(
        FVector4D(Scale.X,    0,    0, 0),
        FVector4D(   0, Scale.Y,    0, 0),
        FVector4D(   0,    0, Scale.Z, 0),
        FVector4D(   0,    0,    0, 1.f)
    );
}

FMatrix4x4 FMatrix4x4::CreateTranslation(const FVector3D& Translation)
{
    return FMatrix4x4(
        FVector4D(1.f, 0, 0, 0),
        FVector4D(0, 1.f, 0, 0),
        FVector4D(0, 0, 1.f, 0),
        FVector4D(Translation,       1.f)
    );
}

FMatrix4x4 FMatrix4x4::CreatePerspective(float FOVDegrees, float AspectRatio, float NearPlane, float FarPlane)
{
    const float TanFov2 = FMath::Tan(FMath::DegreesToRadians(FOVDegrees) * .5f);
    float FarNear = 1.f / (FarPlane - NearPlane);

    /*return FMatrix4x4(
        FVector4D(1.f / (AspectRatio * TanFov2), 0, 0, 0),
        FVector4D(0, 1.f / TanFov2, 0, 0),
        FVector4D(0, 0, -(FarPlane + NearPlane) * FarNear, -1),
        FVector4D(0, 0, -2.f * FarPlane * NearPlane * FarNear, 0)
    );*/
    
    return FMatrix4x4(
            FVector4D(1.f / (AspectRatio * TanFov2), 0, 0, 0),
            FVector4D(0, 1.f / TanFov2, 0, 0),
            FVector4D(0, 0, -(FarPlane + NearPlane) * FarNear, -2.f * FarPlane * NearPlane * FarNear),
            FVector4D(0, 0, -1, 0)
        );
}

FMatrix4x4 FMatrix4x4::CreateOrthographic(float left, float right, float bottom, float top, float nearPlane, float farPlane)
{
    return FMatrix4x4(
        FVector4D(2 / (right - left), 0, 0, 0),
        FVector4D(0, 2 / (top - bottom), 0, 0),
        FVector4D(0, 0, -2 / (farPlane - nearPlane), 0),
        FVector4D(-(right + left) / (right - left), -(top + bottom) / (top - bottom), -(farPlane + nearPlane) / (farPlane - nearPlane), 1)
    );
}

/*
FMatrix4x4 FMatrix4x4::CreateViewMatrixOptimized(const FVector3D& Location, const FQuat& Quat)
{
    FVector4D QuatNormal = FVector4D(Quat).GetSafeNormal();
    
    // Вычисляем базисные векторы напрямую
    float x2 = QuatNormal.X + QuatNormal.X;
    float y2 = QuatNormal.Y + QuatNormal.Y;
    float z2 = QuatNormal.Z + QuatNormal.Z;
    
    float xx2 = QuatNormal.X * x2;
    float xy2 = QuatNormal.X * y2;
    float xz2 = QuatNormal.X * z2;
    
    float yy2 = QuatNormal.Y * y2;
    float yz2 = QuatNormal.Y * z2;
    float zz2 = QuatNormal.Z * z2;
    
    float wx2 = QuatNormal.W * x2;
    float wy2 = QuatNormal.W * y2;
    float wz2 = QuatNormal.W * z2;

    return FMatrix4x4(
        FVector4D(1.0f - (yy2 + zz2), xy2 - wz2,        xz2 + wy2,        -Location.X),
        FVector4D(xy2 + wz2,        1.0f - (xx2 + zz2), yz2 - wx2,        -Location.Y),
        FVector4D(xz2 - wy2,        yz2 + wx2,        1.0f - (xx2 + yy2), -Location.Z),
        FVector4D(0.0f,             0.0f,              0.0f,              1.0f)
    );
}
*/

FMatrix4x4 FMatrix4x4::LookAt(const FVector3D& Eye, const FVector3D& Center, const FVector3D& Up)
{
    const FVector3D f = FVector3D::Normalize(Center - Eye);
    const FVector3D s = FVector3D::Normalize(FVector3D::Cross(f, Up));
    const FVector3D u = FVector3D::Cross(s, f);

    return FMatrix4x4(
        FVector4D( s, -FVector3D::Dot(s, Eye)),
        FVector4D( u, -FVector3D::Dot(u, Eye)),
        FVector4D(-f, FVector3D::Dot(f, Eye)),
        FVector4D(0.f, 0.f, 0.f, 1.f)
    );
}

FVector3D FMatrix4x4::TransformVector(const FVector3D& V) const
{
    return FVector3D(
        V.X * Rows[0][0] + V.Y * Rows[1][0] + V.Z * Rows[2][0],
        V.X * Rows[0][1] + V.Y * Rows[1][1] + V.Z * Rows[2][1],
        V.X * Rows[0][2] + V.Y * Rows[1][2] + V.Z * Rows[2][2]
    );
}

FVector3D FMatrix4x4::TransformPosition(const FVector3D& V) const
{
    const FVector3D& Transform = TransformVector(V);
    return FVector3D(
        Transform.X + Rows[3][0],
        Transform.Y + Rows[3][1],
        Transform.Z + Rows[3][2]);
}

std::array<float,16> FMatrix4x4::ToGLMatrix() const
{
    return {
        Rows[0].X, Rows[1].X, Rows[2].X, Rows[3].X,
        Rows[0].Y, Rows[1].Y, Rows[2].Y, Rows[3].Y,
        Rows[0].Z, Rows[1].Z, Rows[2].Z, Rows[3].Z,
        Rows[0].W, Rows[1].W, Rows[2].W, Rows[3].W
    };
}
/*
std::array<float,16> FMatrix4x4::ToGLMatrix() const
{
    return {
        Rows[0].X, Rows[0].Y, Rows[0].Z, Rows[0].W,
        Rows[1].X, Rows[1].Y, Rows[1].Z, Rows[1].W,
        Rows[2].X, Rows[2].Y, Rows[2].Z, Rows[2].W,
        Rows[3].X, Rows[3].Y, Rows[3].Z, Rows[3].W
    };
}*/

std::string FMatrix4x4::ToString() const
{
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2);

    for (auto row : Rows)
    {
        ss << "| "
           << std::setw(8) << row.X << " "
           << std::setw(8) << row.Y << " "
           << std::setw(8) << row.Z << " "
           << std::setw(8) << row.W << " |\n";
    }

    return ss.str();
}

constexpr FMatrix4x4 FMatrix4x4::Identity = FMatrix4x4(1.f);
constexpr FMatrix4x4 FMatrix4x4::Diagonal = FMatrix4x4(
        FVector4D(1.f, 0.f, 0.f, 0.f),
        FVector4D(0.f, 1.f, 0.f, 0.f),
        FVector4D(0.f, 0.f, 1.f, 0.f),
        FVector4D(0.f, 0.f, 0.f, 1.f)
    );
