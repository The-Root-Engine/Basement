// Root Engine / Basement

#pragma once

#include <cstddef>
#include <cstdint>

using int8    = int8_t;
using int16   = int16_t;
using int32   = int32_t;
using int64   = int64_t;

using uint8   = uint8_t;
using uint16  = uint16_t;
using uint32  = uint32_t;
using uint64  = uint64_t;

using float32 = float;
using float64 = double;

using usize   = std::size_t;    // Signed Size
using ssize   = std::ptrdiff_t; // Unsigned Size

static_assert(sizeof(int8)    == 1, "Invalid int8 size");
static_assert(sizeof(int16)   == 2, "Invalid int16 size");
static_assert(sizeof(int32)   == 4, "Invalid int32 size");
static_assert(sizeof(int64)   == 8, "Invalid int64 size");

static_assert(sizeof(uint8)   == 1, "Invalid uint8 size");
static_assert(sizeof(uint16)  == 2, "Invalid uint16 size");
static_assert(sizeof(uint32)  == 4, "Invalid uint32 size");
static_assert(sizeof(uint64)  == 8, "Invalid uint64 size");

static_assert(sizeof(float32) == 4, "Invalid float32 size");
static_assert(sizeof(float64) == 8, "Invalid float64 size");

static_assert(sizeof(ssize) >= sizeof(usize), "ssize must be at least as wide as usize");
static_assert(sizeof(usize) == sizeof(void*), "usize must match pointer size");
static_assert(sizeof(ssize) == sizeof(void*), "ssize must match pointer size");
