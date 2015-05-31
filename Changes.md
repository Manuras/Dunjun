# Changes

## Big

### Miscellany

* C++11 Uniform Initializer Syntax
	- `Type a{...};` vs `Type a = ...;` etc.
* `var.begin()` -> `std::begin(var)`
* `var.end()` -> `std::end(var)`
* OpenGL Type `object` -> `getNativeHandle() return m_handle`

### ReadOnly

* Removed `ReadOnly`
	- Placed with get/set methods

### Time

* `Time::now()`
	- Unix  - `std::chrono::high_resolution_clock::now()`
	- Win32 - `QueryPerformanceCounter`
		* MSVC does not implement `std::chrono` clocks properly (5ms resolution!)
* Functions definitions in source file <Time.cpp>
* `Time::Zero` constant
* `f32 Time::asSeconds() const`
* `s32 Time::asMilliseconds() const`
* `s64 Time::asMicroseconds() const`

## Medium

* Compiler Detection
* Environment Bit Size Detection
* GL[u]int -> [us]32 etc.
	- Compile-time check of sizes (just to make sure) `<Dunjun/OpenGL.cpp>`
	- OpenGL types are fixed values compared to C/C++ types which can be different sizes
* `push_back` -> `emplace_back`
* ResourceHolder
	- `std::map` -> `std::unordered_map`
* Custom `f16` half-precision floating point - to be used later for data packing

## Small

### Miscellany

* `stringFormat(const char* fmt, ...)`
	- A quick C++ wrapper of snprintf that returns a string
	- Character buffer is only 1024 bytes. If more is needed, use stringstream.
* Templates `class` -> `typename` where appropriate
* Fix Typos

### Math

* `Math::Contansts::` -> `Math::`
* `<cfloat>` -> `<limits>`
* `enum class DrawType : GLenum`

### Window

* `Window::g_ptr` -> `Window::getHandle()` and `Window::setHandle(...)`
* `Window::Dimensions` to store width and height

