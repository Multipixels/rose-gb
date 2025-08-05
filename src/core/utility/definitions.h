#pragma once

#include <cstdint>

typedef struct u3 {
    unsigned int value : 3;
} u3;

typedef struct u4 {
    unsigned int value : 4;
} u4;

using u8 = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;

using s8 = std::int8_t;
using s16 = std::int16_t;
