// Root Engine / Basement

#pragma once

struct FVector2D 
{
    float X, Y;

    explicit constexpr FVector2D()                     : X(0), Y(0) {}
    explicit constexpr FVector2D(float InXY)           : X(InXY), Y(InXY) {}
    explicit constexpr FVector2D(float InX, float InY) : X(InX), Y(InY) {}

    FVector2D operator+(const FVector2D& Other) const { return FVector2D(X + Other.X, Y + Other.Y); }
    FVector2D operator-(const FVector2D& Other) const { return FVector2D(X - Other.X, Y - Other.Y); }
    FVector2D operator*(const FVector2D& Other) const { return FVector2D(X * Other.X, Y * Other.Y); }
    FVector2D operator*(float Scalar)           const { return FVector2D(X * Scalar, Y * Scalar); }

    float LengthSquared() const { return X*X + Y*Y; }
    float Length() const;
    FVector2D GetSafeNormal() const;

    static const FVector2D UpVector;
    static const FVector2D RightVector;
    static const FVector2D DownVector;
    static const FVector2D LeftVector;
};

inline constexpr FVector2D FVector2D::UpVector    = FVector2D(0.f, 1.f);
inline constexpr FVector2D FVector2D::RightVector = FVector2D(1.f, 0.f);
inline constexpr FVector2D FVector2D::DownVector  = FVector2D(0.f, -1.f);
inline constexpr FVector2D FVector2D::LeftVector  = FVector2D(-1.f, 0.f);
