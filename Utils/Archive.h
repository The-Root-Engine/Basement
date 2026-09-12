// ...

#pragma once

#include "Aliases.h"

#include <vector>

enum class EArchiveMode : uint8 { Saving, Loading };

struct FArchive
{

public:
	explicit FArchive(std::vector<uint8>& InBuffer, const EArchiveMode InMode) : Buffer(InBuffer), Mode(InMode) {}

	EArchiveMode GetMode() const { return Mode; }
	bool IsLoading() const { return Mode == EArchiveMode::Loading; }
	bool IsSaving()  const { return Mode == EArchiveMode::Saving;  }
	bool HasError()  const { return bHasError; }
	size_t Tell() const { return Offset; }

	void Seek(const size_t InNewOffset)
	{
		if(InNewOffset < 0 || InNewOffset > static_cast<size_t>(Buffer.size()))
		{
			bHasError = true;
			return;
		}
		Offset = InNewOffset;
	}

	void Serialize(void* InDataPtr, const size_t InNum)
	{
		if(InNum <= 0 || bHasError) return;

		if(IsSaving())
		{
			const size_t OldSize = static_cast<size_t>(Buffer.size());
			Buffer.resize(static_cast<size_t>(OldSize + InNum));
			std::memcpy(Buffer.data() + OldSize, InDataPtr, InNum);
		}
		else
		{
			const size_t End = Offset + InNum;
			if(End > static_cast<size_t>(Buffer.size()))
			{
				bHasError = true;
				return;
			}
			std::memcpy(InDataPtr, Buffer.data() + Offset, InNum);
			Offset += InNum;
		}
	}

private:
	EArchiveMode Mode = EArchiveMode::Saving;
	std::vector<uint8>& Buffer;
	size_t Offset = 0;
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
	Ar.Serialize(&Byte, sizeof(Byte));
	if(Ar.IsLoading()) bValue = (Byte != 0);
	return Ar;
}
