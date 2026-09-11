// Root Engine / Basement

#pragma once

struct FVector2D 
{
    float X, Y;

    explicit FVector2D()                     : X(0), Y(0) {}
    explicit FVector2D(float InXY)           : X(InXY), Y(InXY) {}
    explicit FVector2D(float InX, float InY) : X(InX), Y(InY) {}

    FVector2D operator+(const FVector2D& Other) const { return FVector2D(X + Other.X, Y + Other.Y); }
    FVector2D operator-(const FVector2D& Other) const { return FVector2D(X - Other.X, Y - Other.Y); }
    FVector2D operator*(const FVector2D& Other) const { return FVector2D(X * Other.X, Y * Other.Y); }
    FVector2D operator*(float Scalar)           const { return FVector2D(X * Scalar, Y * Scalar); }

    float LengthSquared() const { return X*X + Y*Y; }
    float Length() const;
    FVector2D GetSafeNormal() const;

    static constexpr FVector2D UpVector;
    static constexpr FVector2D RightVector;
    static constexpr FVector2D DownVector;
    static constexpr FVector2D LeftVector;
};
