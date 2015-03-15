#ifndef DUNJUN_TYPES_HPP
#define DUNJUN_TYPES_HPP

#include <Dunjun/ReadOnly.hpp>

#include <cstdint>
#include <cstddef>

namespace Dunjun
{
// The amount of times that I have swapped between conventions is a lot!
using s8  = std::int8_t;
using s16 = std::int16_t;
using s32 = std::int32_t;
using s64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using usize = std::size_t;

using b8 = bool;
using b32 = s32;

using f32 = float;
using f64 = double;

} // namespace Dunjun

#endif
