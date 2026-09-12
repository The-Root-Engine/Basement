// Root Engine / Basement

#include "Rotator.h"

#include "../Math/Math.h"
#include "Quat.h"

inline FQuat FRotator::ToQuat()
{
    const float HalfPitch = FMath::DegreesToRadians(Pitch) * 0.5f;
    const float HalfYaw   = FMath::DegreesToRadians(Yaw) * 0.5f;
    const float HalfRoll  = FMath::DegreesToRadians(Roll) * 0.5f;

    const float SinPitch = FMath::Sin(HalfPitch);
    const float CosPitch = FMath::Cos(HalfPitch);
    const float SinYaw   = FMath::Sin(HalfYaw);
    const float CosYaw   = FMath::Cos(HalfYaw);
    const float SinRoll  = FMath::Sin(HalfRoll);
    const float CosRoll  = FMath::Cos(HalfRoll);

    return FQuat(
        CosRoll * SinPitch * CosYaw + SinRoll * CosPitch * SinYaw,
        CosRoll * CosPitch * SinYaw - SinRoll * SinPitch * CosYaw,
        SinRoll * CosPitch * CosYaw - CosRoll * SinPitch * SinYaw,
        CosRoll * CosPitch * CosYaw + SinRoll * SinPitch * SinYaw
    );
}
