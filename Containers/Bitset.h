// Root Engine / Basement

#pragma once

#include "../Aliases/Common.h"

template<uint32 NumBits>
class TBitset
{
    
public:
    using BlockType = uint8;
    
    TBitset() = default;
    
    bool operator==(const TBitset& InOther) const { return memcmp(Blocks, InOther.Blocks, sizeof(Blocks)) == 0; }
    bool operator!=(const TBitset& InOther) const { return !(*this == InOther); }
    
    void Set(const uint32 InBitIndex, const bool bValue)
    {
        const uint32 BlockIndex = GetBlockIndex(InBitIndex);
        const BlockType Mask  = MakeBitMask(InBitIndex);
        Blocks[BlockIndex] = (Blocks[BlockIndex] & ~Mask) | (Mask * bValue);
    }
    
    void SetOR(const uint32 InBitIndex, const bool bValue) { Blocks[GetBlockIndex(InBitIndex)] |= MakeBitMask(InBitIndex) * bValue; }
    
    void Reset(const uint32 InBitIndex) { Set(InBitIndex, false); }
    bool Get(const uint32 InBitIndex) const { return (Blocks[GetBlockIndex(InBitIndex)] & MakeBitMask(InBitIndex)) != 0; }
    void Flip(const uint32 InBitIndex) { Blocks[GetBlockIndex(InBitIndex)] ^= MakeBitMask(InBitIndex); }
    
    void Empty() { Fill(false); }
    void Fill(const bool bValue) { memset(Blocks, (~static_cast<BlockType>(0)) * bValue, sizeof(Blocks)); }

// private:
    static constexpr uint32 BitsPerBlock = sizeof(BlockType) * 8;
    static constexpr uint32 NumBlocks = (NumBits + BitsPerBlock - 1) / BitsPerBlock;
    
    BlockType Blocks[NumBlocks] = {};
    
    static constexpr uint32 GetBlockIndex(const uint32 InBitIndex) { return InBitIndex / BitsPerBlock; }
    static constexpr BlockType MakeBitMask(const uint32 InBitIndex) { return static_cast<BlockType>(1) << (InBitIndex % BitsPerBlock); }
};
