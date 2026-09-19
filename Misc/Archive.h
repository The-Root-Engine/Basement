// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"
#include "../Containers/Array.h"

enum class EArchiveMode : uint8 { Saving, Loading };

struct FArchive
{

public:
	explicit FArchive(TArray<uint8>& InBuffer, const EArchiveMode InMode) : Mode(InMode), Buffer(&InBuffer) {}
	
	EArchiveMode GetMode() const { return Mode; }
	bool IsLoading() const { return Mode == EArchiveMode::Loading; }
	bool IsSaving()  const { return Mode == EArchiveMode::Saving;  }
	bool HasError()  const { return bHasError; }
	usize Tell() const { return Offset; }
	
	void Seek(const usize InNewOffset)
	{
		if(InNewOffset < 0 || InNewOffset > static_cast<usize>(Buffer->Num()))
		{
			bHasError = true;
			return;
		}
		Offset = InNewOffset;
	}
	
	void Serialize(void* InDataPtr, const usize InNum)
	{
		if(InNum <= 0 || bHasError) return;
		
		if(IsSaving())
		{
			const usize OldSize = static_cast<usize>(Buffer->Num());
			Buffer->SetNum(static_cast<usize>(OldSize + InNum));
			memcpy(Buffer->Data() + OldSize, InDataPtr, InNum);
		}
		else
		{
			const usize End = Offset + InNum;
			if(End > static_cast<usize>(Buffer->Num()))
			{
				bHasError = true;
				return;
			}
			memcpy(InDataPtr, Buffer->Data() + Offset, InNum);
			Offset += InNum;
		}
	}

private:
	EArchiveMode Mode = EArchiveMode::Saving;
	TArray<uint8>* Buffer;
	usize Offset = 0;
	bool bHasError = false;
};

inline FArchive& operator^(FArchive& Ar, int8&   Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }
inline FArchive& operator^(FArchive& Ar, int16&  Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }
inline FArchive& operator^(FArchive& Ar, int32&  Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }
inline FArchive& operator^(FArchive& Ar, int64&  Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }

inline FArchive& operator^(FArchive& Ar, uint8&  Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }
inline FArchive& operator^(FArchive& Ar, uint16& Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }
inline FArchive& operator^(FArchive& Ar, uint32& Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }
inline FArchive& operator^(FArchive& Ar, uint64& Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }

inline FArchive& operator^(FArchive& Ar, float&  Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }
inline FArchive& operator^(FArchive& Ar, double& Value) { Ar.Serialize(&Value, sizeof(Value)); return Ar; }

inline FArchive& operator^(FArchive& Ar, bool& bValue)
{
	uint8 Byte = bValue ? 1 : 0;
	Ar ^ Byte;
	if(Ar.IsLoading()) bValue = (Byte != 0);
	return Ar;
}

template<typename Enum>
inline Meta::EnableIf<Meta::IsEnum<Enum>, FArchive&> operator^(FArchive& Ar, Enum& EnumValue)
{
	using UnderlyingType = __underlying_type(Enum);
	UnderlyingType EnumRaw = static_cast<UnderlyingType>(EnumValue);
	Ar ^ EnumRaw;
	if(Ar.IsLoading()) EnumValue = static_cast<Enum>(EnumRaw);
	return Ar;
}

template<typename T>
inline Meta::EnableIf<!Meta::IsEnum<T>, FArchive&> operator^(FArchive& Ar, T& Value)
{
	Ar.Serialize(&Value, sizeof(T));
	return Ar;
}
