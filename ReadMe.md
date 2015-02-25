# Dunjun #
This project will be documenting and demonstrating the development of making a game from scratch*! Every step of the game development process and every line of code will be explained thoroughly.

The game will be a 3D rogue-like-*like* dungeon crawler style game. More will be revealed about the game as the project persists.

YouTube Channel: [GingerGames](https://youtube.com/c/GingerGames)

GitHub: [Dunjun GitHub](https://github.com/gingerBill/Dunjun)

**With minimal libraries such as GLFW, GLEW, and the STB libraries.*

## YouTube Playlist ##

[Dunjun Playlist](https://www.youtube.com/playlist?list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e)

## Episode List ##

### Introduction ###

* [000 - Introduction](https://www.youtube.com/watch?v=fRUYl6_5m3o&index=1&list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e)

### Bare Bones ###

* [001 - Project Setup (Visual Studio)](https://www.youtube.com/watch?v=Vzve8VOn8qA&index=2&list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e)
* [002 - Creating a Window (GLFW3)](https://www.youtube.com/watch?v=LNxpDcRs8Zg&list=PL93bFkoCMJslJJb15oQddnmABNUl6iz8e&index=3)
* [003 - Drawing with OpenGL (GLEW)](https://www.youtube.com/watch?v=42x_p1PeecU)
* [004 - Shader Program Class](https://www.youtube.com/watch?v=fLSLJ66AEOU)
* [005 - Textures (STB)](https://www.youtube.com/watch?v=eiz7ZZBtUA0)
* [006 - Image Loader](https://www.youtube.com/watch?v=Wl0jh_CBT8w)
* [007 - Texture Wrapper](https://www.youtube.com/watch?v=2i2jX4yb8sI)
* [008 - Error Handling & Code Tidying](https://www.youtube.com/watch?v=jUUGEFV7rk0)

### Vectors and Matrices ###

* [009 - Introduction to Transformations with Matrices](https://www.youtube.com/watch?v=imjaU0gO1vY)
* [010 - Implement Basic Vector Types](https://www.youtube.com/watch?v=MSHeE7kAqbA)
* [011 - Vector Functions](https://www.youtube.com/watch?v=sX_1BSVp-ok)
* [012 - Matrix4 Type](https://www.youtube.com/watch?v=fcHEk02Hasg)
* [013 - Matrix Transform Functions](https://www.youtube.com/watch?v=WEpA4NbN-xQ)
* [014 - View & Projection Matrices & Angles](https://www.youtube.com/watch?v=QAIbGN_oXdo)
* [015 - Constants, Code Tidying & GLSL Convention](https://www.youtube.com/watch?v=hQw7_DWjQtg)

### Model Assets and Model Instances ###

* [016 - ModelAssets & ModelInstances](https://www.youtube.com/watch?v=oDwALlxMa4k)

### Quaternions and Rotations in 3D ###

* [017 - Introduction to Complex Numbers](https://www.youtube.com/watch?v=NpkoqTOWn4E)
* [018 - Introduction to Quaternions](https://www.youtube.com/watch?v=Vhtw7EvLuQQ)
* [019 - Quaternion Interpolation](https://www.youtube.com/watch?v=GFnWLM_HcKw)
* [020 - Implement Quaternions](https://www.youtube.com/watch?v=7rZWS_62rXY)
* [021 - Quaternion Functions](https://www.youtube.com/watch?v=8pUqEspcS8w)
* [022 - Transform Type](https://www.youtube.com/watch?v=XVkJkczl6tM)

### Camera and Input ###

* [023 - Fixed Time Step & Code Tidying](https://www.youtube.com/watch?v=t5mZi9bJX3A)
* [024 - ReadOnly Types & Camera Type](https://www.youtube.com/watch?v=l-DFRShm5wE)
* [025 - Complete Camera & Depth Testing](https://www.youtube.com/watch?v=30QORMjrpKA)
* [026 - Basic First Person Camera Input](https://www.youtube.com/watch?v=dkYK0e0m_H0)
* [027 - Game Separation and Input Wrapper](https://www.youtube.com/watch?v=9bpZjQYPXqg)
* [028 - XInput Gamepads](https://www.youtube.com/watch?v=NAVaHMDNPjQ)
* 029 - Gamepad Camera Control
* 030 - Mouse Buttons and Scroll Input


## Contact ##

* YouTube: [GingerGames](https://youtube.com/c/GingerGames)
* Email: dunjun@gingerBill.org
* GitHub: [Dunjun GitHub](https://github.com/gingerBill/Dunjun)

## FAQ ##

### Will this be a simple game, for teaching purposes? ###

No! In fact, the game design has been made to require *complex concepts* which exist in more than most game designs.

### Are the accompanying videos just recordings of someone programming? ###

No! 99%* of the programming for the game is recorded in the videos; every step of the game development process and every line of code will be explained thoroughly.

**Some of the code will not programmed in the videos but this will mostly be bug fixes or minor changes to the code that can be explained quickly.*

### What platforms will this game support? ###

This game will support Windows, Mac OS X, and Linux.

### I have a problem with X... ###

Please feel free to contact with any problem:

* YouTube: [GingerGames](https://youtube.com/c/GingerGames)
* Email: dunjun@gingerBill.org
* GitHub: [Dunjun GitHub](https://github.com/gingerBill/Dunjun)

## Prerequisites ##

Before we can begin, you need to make sure you have all the things you will need.

* A reasonable amount of experience with C++
	- C++11 experience will help
* Graphics card compatible with OpenGL 2.1
	- DirectX 9 Equivalent Cards
* Text Editor and C++11 Compiler, or IDE (MSVC 12 compiler capabilities at least)
* The initial libraries:
	- GLFW - For creating the context, window, and handling input
	- GLEW - To use new OpenGL functions

## Building ##

At the moment, only Windows is supported through the Visual Studio solution. Mac OS X and Linux will implemented later when needed/wanted.

Most of the code should compile on Mac OS X and Linux with probably only a few minor changes.

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
* More below!

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

camelCase (e.g. temp, m\_world, s\_time)

### Variable Prefixes ###

* m_ for protected/private member variables
* s_ for static variables
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

* HACK  - don't use in production (similar to FIXME but still works)
* FIXME - fix as soon as possible (does not work as intended)
* TODO  - todo
* NOTE  - note to reader (can be used in conjunction with TODO)

Example:

```c++
// TODO(bill): This is some example text for a todo. That
//             spans multiple lines.
//             This annotation was written by bill as
//             indicated next to the annotation

```
