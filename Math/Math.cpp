// Root Engine / Basement

#pragma once

#include "Math.h"

#include <cmath>

float FMath::Sqrt(const float InF) { return sqrt(InF); }

float FMath::Sin(const float InRadians) { return sin(InRadians); }
float FMath::Cos(const float InRadians) { return cos(InRadians); }
float FMath::Tan(const float InRadians) { return tan(InRadians); }
float FMath::Asin(const float InF) { return asin(Clamp(InF, -1.f, 1.f)); }
float FMath::Acos(const float InF) { return acos(Clamp(InF, -1.f, 1.f)); }
float FMath::Atan2(const float InY, float InX) { return atan2(InY, InX); }
