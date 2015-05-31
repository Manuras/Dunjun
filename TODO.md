# TODO #

## SDL Debate

* Swap from GLFW3 to SDL2? Reasons:
	- No need for custom OS specific input code
	- Better controller support
	- Force/Haptic feedback (No need for manual XInput handling)
	- Key mapping
	- Pre-built Event System (possible in GLFW but has to be made)
	- SDL_GetBasePath()
	- CPU Feature Detection
	- Endian Detection and Independence
		* Just in case we needed to port to ARM/PPC/etc which are big-endian compared to x86(-64) which is little-endian
	- SDL_ShowSimpleMessageBox
		* Information
		* Warning
		* Error
	- Mature Library
* Reasons not to:
	- SDL likes you to make an _SDL app_ rather than an _app using SDL_
	- More dependencies than GLFW
	- A little more "messy" than GLFW
	- SDL does a lot more than GLFW but not all of it has to be used
		* Prefer C++(11) stdlib when appropriate
* If SDL2 is used?
	- SDL2_mixer vs OpenAL/ALmixer
	- **DO NOT USE** SDL2_audio
	- No need for `SDL_image` as `stb_image` is used

## Audio

* SDL2_mixer vs OpenAL/ALmixer vs Software Audio

## Rendering

* Font Loading
* Text Rendering
* GUI Elements

* Physically Based Rendering
* Material System
	- Use `enum` but if a custom shader is needed, allow for it.
	```c++
	enum class ShaderType
	{
		Default,
		One,
		Two,
		...,
		Custom // Material::shaders != nullptr
	};

	struct Material
	{
		ShaderType           shaderType{ShaderType::Default};
		const ShaderProgram* shaders{nullptr};
		...
	};
	```
* Shadows
	- Maps (GPU based but "blurry")
	- Volumes (Pixel Perfect but CPU based)

## Settings

* Config/Settings Files & Parser
	- Self implement
		* INI - `name=value` - Very simple but can be restrictive
		* Static INI (INI with static types) - `name: type = value` - "compile-time" error-checking (P.S. I came up with a while ago and it works well as there is no need for Hungarian Notation *Yuk!*)
	- Library
		* TOML - `name = value` - More of an extended INI
		* JSON - `"name": "value"`
		* SQLite - Fast and versatile but big and requires more work to implement tools
		* XML is ugly and verbose and Goddamn awful!
		* YAML is too complicated and enforces spaces
* Resolution swapping without restarting
* Monitor swapping for fullscreen
* VSync - That actually works well!
* Key mapping - Save/Open File - Through config files
* Quality Settings
	- Window Resolution
	- RT Resolution (Super/Sub-Rendering)
	- Gamma, Brightness, Contrast, etc.
	- Max number of lights
	- Max number of shadow maps
	- etc.
* HiDPI - Mac OS X Retina etc. - I have no experience here so I will probably need help.
