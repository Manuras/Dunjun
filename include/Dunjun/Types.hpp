#ifndef DUNJUN_TYPES_HPP
#define DUNJUN_TYPES_HPP

#include <Dunjun/ReadOnly.hpp>

#include <cstddef>

namespace Dunjun
{
// All "common" platforms use the same size for char, short and int
// We do not need to include stdint.h/cstdint

// The amount of times that I have swapped between conventions is a lot!
using s8 = signed char;
using u8 = unsigned char;

using s16 = signed short;
using u16 = unsigned short;

using s32 = signed int;
using u32 = unsigned int;

// Older versions of MSVC do not defined long long as 64 bits so just in case
#if defined(_MSC_VER)
using s64 = signed __int64;
using u64 = unsigned __int64;
#else
using s64 = signed long long;
using u64 = unsigned long long;
#endif

using usize = std::size_t;

using bool32 = s32; // NOTE(bill): might change to b32?

using f32 = float;
using f64 = double;

} // namespace Dunjun

#endif
