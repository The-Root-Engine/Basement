// Root Engine / Basement

#pragma once

#include "Math/Math.h"

struct FAngle
{
	
public:
	static constexpr float DegreesToByte = 256.0f / 360.0f;
	static constexpr float ByteToDegrees = 360.0f / 256.0f;
	static constexpr float RadiansToByte = 256.0f / (2.0f * FMath::Pi);
	static constexpr float ByteToRadians = (2.0f * FMath::Pi) / 256.0f;
	
	explicit constexpr FAngle()                : Data(0) {}
	explicit constexpr FAngle(uint8 InRawData) : Data(InRawData) {}
	
	static constexpr FAngle FromDegrees(float InDegrees) { return FAngle(static_cast<uint8>(InDegrees >= 0 ? (InDegrees * DegreesToByte + 0.5f) : (InDegrees * DegreesToByte - 0.5f))); }
	static constexpr FAngle FromRadians(float InRadians) { return FAngle(static_cast<uint8>(InRadians >= 0 ? (InRadians * RadiansToByte + 0.5f) : (InRadians * RadiansToByte - 0.5f))); }
	
	float GetDegrees() const { return static_cast<float>(Data) * ByteToDegrees; }
	float GetRadians() const { return static_cast<float>(Data) * ByteToRadians; }
	
	FAngle operator+(const FAngle& Other) const { return FAngle(Data + Other.Data); }
	FAngle operator-(const FAngle& Other) const { return FAngle(Data - Other.Data); }
	bool operator==(const FAngle& Other) const { return Data == Other.Data; }
	bool operator!=(const FAngle& Other) const { return Data != Other.Data; }
	FAngle operator-() const { return FAngle(static_cast<uint8>(-static_cast<int8>(Data))); }
	
	static FAngle Lerp(FAngle A, FAngle B, float Alpha) { return FAngle(A.Data + static_cast<uint8>(static_cast<float>(static_cast<int8>(B.Data - A.Data)) * Alpha)); }
	
	// constexpr FAngle operator "" _deg(uint16 Deg) { return FAngle::FromDegrees(static_cast<float>(Deg)); }

private:
	uint8 Data;
};
