# Dunjun #
This project will be documenting and demonstrating the development of making a game from scratch (using minimal libraries).
Every step of the game development process and every line of code will be explained thoroughly.

The game will be a 3D rogue-like*-like* dungeon crawler style game.

## Youtube Playlist ##

[Dunjun Playlist](https://www.youtube.com/playlist?list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e)


## Episode List ##

* [000 - Introduction](https://www.youtube.com/watch?v=fRUYl6_5m3o&index=1&list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e)
* [001 - Project Setup (Visual Studio)](https://www.youtube.com/watch?v=Vzve8VOn8qA&index=2&list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e)
* [002 - Creating a Window (GLFW3)](https://www.youtube.com/watch?v=LNxpDcRs8Zg&list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e&index=3)
* [003 - Drawing with OpenGL (GLEW)](https://www.youtube.com/watch?v=42x_p1PeecU)
* [004 - Shader Program Class](https://www.youtube.com/watch?v=fLSLJ66AEOU)
* [005 - Textures (STB)](https://www.youtube.com/watch?v=eiz7ZZBtUA0)
* [006 - Image Loader](https://www.youtube.com/watch?v=Wl0jh_CBT8w)
* [007 - Texture Wrapper](https://www.youtube.com/watch?v=2i2jX4yb8sI)
* [008 - Error Handling & Code Tidying](https://www.youtube.com/watch?v=jUUGEFV7rk0)
* [009 - Introduction to Transformations with Matrices](https://www.youtube.com/watch?v=imjaU0gO1vY)
* [010 - Implement Basic Vector Types](https://www.youtube.com/watch?v=MSHeE7kAqbA)
* [011 - Vector Functions](https://www.youtube.com/watch?v=sX_1BSVp-ok)
* [012 - Matrix4 Type](https://www.youtube.com/watch?v=fcHEk02Hasg)
* [013 - Matrix Transform Functions](https://www.youtube.com/watch?v=WEpA4NbN-xQ)
* [014 - View & Projection Matrices & Angles](https://www.youtube.com/watch?v=QAIbGN_oXdo)
* [015 - Constants, Code Tidying & GLSL Convention](https://www.youtube.com/watch?v=hQw7_DWjQtg)
* [016 - ModelAssets & ModelInstances](https://www.youtube.com/watch?v=oDwALlxMa4k)
* [017 - Introduction to Complex Numbers](https://www.youtube.com/watch?v=NpkoqTOWn4E)
* [018 - Introduction to Quaternions](https://www.youtube.com/watch?v=Vhtw7EvLuQQ)
* [019 - Quaternion Interpolation](https://www.youtube.com/watch?v=GFnWLM_HcKw)
* [020 - Implement Quaternions](https://www.youtube.com/watch?v=7rZWS_62rXY)
* 021 - Quaternion Functions
* 022 - Transform Type
* 023 - Fixed Time Step & Code Tidying

## Contact ##

* Youtube: [GingerGames](https://youtube.com/c/GingerGames)
* Email: dunjun@gingerbill.org
* GitHub: [Dunjun GitHub](https://github.com/gingerBill/Dunjun)

## FAQ ##

### Will this be a simple game, for teaching purposes? ###

No! In fact, the game design has been made to require *complex concepts* which exist in more than most game designs.

### Are the accompanying videos just recordings of someone programming? ###

No! Although 99%* of the programming for the game is recorded in the videos, every step of the game development process and every line of code will be explained thoroughly.

### What platforms will this game support? ###

This game will support Windows, Mac OS X, and Linux.

### I have a problem with X... ###

Please feel free to contact with any problem:

* Youtube: [GingerGames](https://youtube.com/c/GingerGames)
* Email: dunjun@gingerbill.org
* GitHub: [Dunjun GitHub](https://github.com/gingerBill/Dunjun)

## Building ##

At the moment, only Windows is supported through the visual studio solution. Mac OS X and Linux will implemented later when needed/wanted.

## Supported Platforms ##

Graphics APIs:

* *OpenGL* 2.1 (through GLEW)

Platforms:

* *Windows* (Through MSVC 12)
* *OS X* (To be added)
* *Linux* (To be added)

## Dependencies ##

### Tools ###

* C++ compiler with decent C++11 support
	- If Visual Studio, please use *at least* MSVC 12.

### Libraries ###

* OpenGL (Rendering)
* GLFW 3.1 (Window, Input and, Context Handling)
* GLEW (OpenGL Extension Wrangler Library)
* STB Libraries (Image and Font Loading)

## Conventions ##

* See clang-format-style.yaml for formatting style
* Allman Indenting
* CamelCase
* Tabs for indentation
* Spaces for alignment
* TODO!

### Classes ###

PascalCase (Upper CamelCase) (e.g. ShaderProgram)

### Functions, Methods, and Variables ###

camelCase (e.g. loadFromFile)

### Namespaces ###

PascalCase (e.g. Dunjun::)

The end of a namespace must appended by `namespace` then its name.

Example:

```c++
namespace Dunjun
{
namespace Inner
{
...
} // namespace Inner
} // namespace Dunjun
```


### Using and Typedef ###

In C++11, `using` is a superset of `typedef`. `using` is preferred in this style guide.

```c++
// Using
using FooBar = std::pair<Foo, Bar>;
// Typedef
typedef std::pair<Foo, Bar> FooBar;
```

### Comments ###

C++ style comments `//` are preferred but C-style comments `/**/` can be used. The reasoning is that C-style comments cannot be nested and most IDEs/Editors can comments whole blocks in the C++ style which can allow for uncommenting a single line easily.

### Arrays and Vectors ###

When an collection of data is needed, use a `std::vector` unless it is fixed at runtime. If it is fixed at runtime use a classic C array or `std::array`. `std::array` is preferred as it is more C++ but they are exactly the same as it is just a class version of the classic C array.

The vector's elements are guaranteed to be contiguous, so you can pass `&v[0]` to any function expecting a pointer to an array; e.g., C library routines, OpenGL. Also, `std::vector<char> buffer(2048);` is a brilliant way to allocate a local buffer.

Use `std::vector` **unless** the profiler says that there is a problem **and** the array is tiny.

### Pointers ###

Raw pointers (e.g. Bar*) can be used, but if a smart pointer can be used, please do so.

Shorthand for smart pointers (`std::unique_ptr`, `std::shared_ptr`, `std::weak_ptr`) of classes can be declared with using.

* UPtr -> unique_ptr
* SPtr -> shared_ptr
* WPtr -> weak_ptr

Do not use `auto_ptr`, use `unique_ptr` as it is much better and `auto_ptr` is depreciated.
`std::shared_ptr`s are to be use sparingly.

Example:

```c++
class Bar
{
public:
	using UPtr = std::unique_ptr<Bar>;
	using SPtr = std::shared_ptr<Bar>;
	...
};
```

If a class/etc. does not need a certain smart pointer, do not give a shorthand.

### Variables ###

camelCase (e.g. temp, m_world, s_time)

### Variable Prefixes ###

* m_ for protected/private member variables
* s_ for static variables (non const)
* g_ for global variables (*should* never be used! (except on a few rare occasions but if done so, place them within a namespace, at least!))


Example:

```c++
extern int g_thingy;

class Foo
{
	GLOBAL unsigned long s_time;

private:
	char m_letter;
};
```


### Defines ###

In `Dunjun/Common.hpp`, there are some defines for static:

```c++
#define GLOBAL static
#define INTERNAL static
#define LOCAL_PERSIST static
```

Please using these rather than the keyword static to indicate which type of static is being used.

Example:

```c++
GLOBAL int g_thingy;

INTERNAL void doSomething()
{
	LOCAL_PERSIST char buffer[10];

	...
}
```

### Annotations ###

* HACK  - don't use in production
* FIXME - fix as soon as possible
* TODO  - todo
* NOTE  - note to reader

Example:

```c++
// TODO(bill): This is some example text for a todo. That
//             spans multiple lines.

```
