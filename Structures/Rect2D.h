// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "Vector2D.h"

template<typename T>
struct TRect2D
{
    
public:
    TVector2D<T> Location;
    TVector2D<T> Size;
    using ScalarType = T;
    
    constexpr TRect2D() : Location(0), Size(1) {}
    explicit constexpr TRect2D(const TVector2D<T> InLocation, const TVector2D<T> InSize) : Location(InLocation), Size(InSize) {}
    explicit constexpr TRect2D(const T InLocationX, const T InLocationY, const T InSizeX, const T InSizeY) : Location(InLocationX, InLocationY), Size(InSizeX, InSizeY) {}
    
    static constexpr TRect2D FromCenterAndHalfSize(const TVector2D<T> InCenter, const TVector2D<T> InHalfSize) { return TRect2D(InCenter - InHalfSize, InHalfSize * 2); }
    static constexpr TRect2D FromCenterAndHalfSize(const T InCenterX, const T InCenterY, const T InHalfSizeX, const T InHalfSizeY) { return TRect2D(InCenterX - InHalfSizeX, InCenterY - InHalfSizeY, InHalfSizeX * 2, InHalfSizeY * 2); }
    
    constexpr TVector2D<T> Min() const { return Location; }
    constexpr TVector2D<T> Max() const { return Location + Size; }
    constexpr TVector2D<T> Center() const { return Location + (Size * static_cast<T>(0.5)); }
    
    constexpr bool IsInside(const TVector2D<T>& Point) const
    {
        return Point.X >= Min().X && Point.X < Max().X &&
               Point.Y >= Min().Y && Point.Y < Max().Y;
    }
    
    constexpr bool Intersects(const TRect2D& Other) const 
    {
        return Min().X <= Other.Max().X && Max().X >= Other.Min().X &&
               Min().Y <= Other.Max().Y && Max().Y >= Other.Min().Y;
    }
};

using FRect2DInt8   = TRect2D<int8  >;
using FRect2DInt16  = TRect2D<int16 >;
using FRect2DInt32  = TRect2D<int32 >;
using FRect2DInt64  = TRect2D<int64 >;
using FRect2DUint8  = TRect2D<uint8 >;
using FRect2DUint16 = TRect2D<uint16>;
using FRect2DUint32 = TRect2D<uint32>;
using FRect2DUint64 = TRect2D<uint64>;
using FRect2DFloat  = TRect2D<float >;
using FRect2DDouble = TRect2D<double>;

using FRect2D = FRect2DInt32;
