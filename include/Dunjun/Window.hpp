#ifndef DUNJUN_WINDOW_HPP
#define DUNJUN_WINDOW_HPP

#include <Dunjun/Math.hpp>

#include <Dunjun/OpenGL.hpp>
#include <GLFW/glfw3.h>

#include <string>

namespace Dunjun
{
namespace Window
{
struct Dimensions
{
	int width;
	int height;

	inline f32 aspectRatio() const
	{
		if (width == height)
			return 1.0f;

		return static_cast<f32>(width) / static_cast<f32>(height);
	}
};

GLFWwindow* getHandle();
void setHandle(GLFWwindow* w);

bool init();
void cleanup();

GLFWwindow* createWindow(GLFWmonitor* monitor = nullptr);
GLFWwindow* createWindow(Dimensions size, GLFWmonitor* monitor = nullptr);
void destroyWindow();
void destroyWindow(GLFWwindow* w);

void makeContextCurrent();
void swapInterval(int i);
bool shouldClose(); // Or should it be isOpen() ?

void swapBuffers(); // or should it be display() ?
void pollEvents();

void setTitle(const std::string& title);

bool isFullscreen();
void setFullscreen(bool fullscreen);

Dimensions getWindowSize();
Dimensions getFramebufferSize();

bool isInFocus();
bool isIconified();

// void setIcon(const Image& image);
// void setFramerateLimit(u32 limit);
// void setVerticalSyncEnabled(bool enabled);
// bool hasFocus();

// TODO(bill): Event System
// // Pop the event on top of the event queue, if any, and return it
// bool pollEvent(Event& event);
// // Wait for an event and return it
// bool waitEvent(Event& event);

} // namespace Window
} // namespace Dunjun

#endif
