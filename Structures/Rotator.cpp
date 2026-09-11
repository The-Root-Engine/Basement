// Root Engine / Basement

#include "Rotator.h"
#include "Math.h"
#include "Quat.h"

inline FQuat FRotator::ToQuat()
{
    float HalfPitch = FMath::DegreesToRadians(Pitch) * 0.5f;
    float HalfYaw   = FMath::DegreesToRadians(Yaw) * 0.5f;
    float HalfRoll  = FMath::DegreesToRadians(Roll) * 0.5f;

    float SinPitch = FMath::Sin(HalfPitch);
    float CosPitch = FMath::Cos(HalfPitch);
    float SinYaw   = FMath::Sin(HalfYaw);
    float CosYaw   = FMath::Cos(HalfYaw);
    float SinRoll  = FMath::Sin(HalfRoll);
    float CosRoll  = FMath::Cos(HalfRoll);

    return FQuat(
        CosRoll * SinPitch * CosYaw + SinRoll * CosPitch * SinYaw,
        CosRoll * CosPitch * SinYaw - SinRoll * SinPitch * CosYaw,
        SinRoll * CosPitch * CosYaw - CosRoll * SinPitch * SinYaw,
        CosRoll * CosPitch * CosYaw + SinRoll * SinPitch * SinYaw
    );
}

void FRotator::Normalize()
{
    Pitch = FMath::NormalizeAngle(Pitch);
    Yaw = FMath::NormalizeAngle(Yaw);
    Roll = FMath::NormalizeAngle(Roll);
}

FRotator FRotator::GetNormalized() const
{
    return FRotator(
        FMath::NormalizeAngle(Pitch),
        FMath::NormalizeAngle(Yaw),
        FMath::NormalizeAngle(Roll)
    );
}
