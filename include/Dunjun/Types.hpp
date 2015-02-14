#ifndef DUNJUN_TYPES_HPP
#define DUNJUN_TYPES_HPP

#include <cstdint>
#include <cstddef>

namespace Dunjun
{
using i8  = std::int8_t;
using i16 = std::int16_t;
using i32 = std::int32_t;
using i64 = std::int64_t;

using u8  = std::uint8_t;
using u16 = std::uint16_t;
using u32 = std::uint32_t;
using u64 = std::uint64_t;

using usize = std::size_t;

using b8 = bool;
using b32 = i32;

using f32 = float;
using f64 = double;

/*
// NOTE(bill): Alternative Version that I may use instead
//             Keep using short version for now.
using int8  = std::int8_t;
using int16 = std::int16_t;
using int32 = std::int32_t;
using int64 = std::int64_t;

using uint8  = std::uint8_t;
using uint16 = std::uint16_t;
using uint32 = std::uint32_t;
using uint64 = std::uint64_t;

using usize = std::size_t;

using bool8 = bool;
using bool32 = i32;

using float32 = float;
using float64 = double;
*/

} // namespace Dunjun

#endif
