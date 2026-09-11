// Root Engine / Basement

#pragma once

struct FQuat;

struct FRotator 
{
    float Pitch;
    float Yaw;
    float Roll;
	
    explicit FRotator() : Pitch(0.f), Yaw(0.f), Roll(0.f) {}
    explicit FRotator(float InPitch, float InYaw, float InRoll) : Pitch(InPitch), Yaw(InYaw), Roll(InRoll) {}

    FQuat ToQuat();
    
    void Normalize();
    
    FRotator GetNormalized() const;
};
