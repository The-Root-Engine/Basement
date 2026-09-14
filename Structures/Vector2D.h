// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "../Math/Math.h"

template<typename T>
struct TVector2D
{
    
public:
    T X;
    T Y;
    using ScalarType = T;
    
    constexpr TVector2D() : X(0), Y(0) {}
    explicit constexpr TVector2D(const T InF) : X(InF), Y(InF) {}
    explicit constexpr TVector2D(const T InX, const T InY) : X(InX), Y(InY) {}
    template<typename U> constexpr TVector2D(const TVector2D<U>& InOther) : X(static_cast<T>(InOther.X)), Y(static_cast<T>(InOther.Y)) {}
    
    constexpr TVector2D operator-() const { return { -X, -Y }; }
    constexpr TVector2D operator+(const TVector2D& InOther) const { return TVector2D(X + InOther.X, Y + InOther.Y); }
    constexpr TVector2D operator-(const TVector2D& InOther) const { return TVector2D(X - InOther.X, Y - InOther.Y); }
    constexpr TVector2D operator*(const TVector2D& InOther) const { return TVector2D(X * InOther.X, Y * InOther.Y); }
    constexpr TVector2D operator/(const TVector2D& InOther) const { return TVector2D(X / InOther.X, Y / InOther.Y); }
    constexpr TVector2D operator*(const T InScalar) const { return TVector2D(X * InScalar, Y * InScalar); }
    constexpr TVector2D operator/(const T InScalar) const { return TVector2D(X / InScalar, Y / InScalar); }
    
    constexpr TVector2D& operator+=(const TVector2D& InOther) { *this = *this + InOther; return *this; }
    constexpr TVector2D& operator-=(const TVector2D& InOther) { *this = *this - InOther; return *this; }
    constexpr TVector2D& operator*=(const TVector2D& InOther) { *this = *this * InOther; return *this; }
    constexpr TVector2D& operator/=(const TVector2D& InOther) { *this = *this / InOther; return *this; }
    constexpr TVector2D& operator*=(const T InScalar) { *this = *this * InScalar; return *this; }
    constexpr TVector2D& operator/=(const T InScalar) { *this = *this / InScalar; return *this; }
    
    float LengthSquared() const { return X*X + Y*Y; }
    float Length() const { return FMath::Sqrt(LengthSquared()); }
    TVector2D GetSafeNormal() const { const T Len = Length(); return FMath::IsNearlyZero(Len) ? TVector2D(0) : *this * (1.f / Len); }
    TVector2D Floor() const { return TVector2D(FMath::Floor(X), FMath::Floor(Y)); }
    
    static const TVector2D UpVector;
    static const TVector2D RightVector;
    static const TVector2D DownVector;
    static const TVector2D LeftVector;
};

template<typename T> inline constexpr TVector2D<T> TVector2D<T>::UpVector    = TVector2D( 0,  1);
template<typename T> inline constexpr TVector2D<T> TVector2D<T>::RightVector = TVector2D( 1,  0);
template<typename T> inline constexpr TVector2D<T> TVector2D<T>::DownVector  = TVector2D( 0, -1);
template<typename T> inline constexpr TVector2D<T> TVector2D<T>::LeftVector  = TVector2D(-1,  0);

using FVector2DInt8   = TVector2D<int8  >;
using FVector2DInt16  = TVector2D<int16 >;
using FVector2DInt32  = TVector2D<int32 >;
using FVector2DInt64  = TVector2D<int64 >;
using FVector2DUint8  = TVector2D<uint8 >;
using FVector2DUint16 = TVector2D<uint16>;
using FVector2DUint32 = TVector2D<uint32>;
using FVector2DUint64 = TVector2D<uint64>;
using FVector2DFloat  = TVector2D<float >;
using FVector2DDouble = TVector2D<double>;

using FVector2D = FVector2DFloat;
