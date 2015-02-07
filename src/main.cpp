#include <Dunjun/OpenGL.hpp>
#include <Dunjun/Common.hpp>
#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/Texture.hpp>

#include <Dunjun/OpenGL.hpp>

#include <GLFW/glfw3.h>

#include <stb/stb_easy_font.h>

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include <sstream>

class Clock
{
public:
	inline double getElapsedTime() const { return glfwGetTime() - m_startTime; }

	double restart()
	{
		double now = glfwGetTime();
		double elapsed = now - m_startTime;
		m_startTime = now;

		return elapsed;
	}

private:
	double m_startTime = glfwGetTime();
};

class TickCounter
{
public:
	bool update(double period)
	{
		bool reset = false;
		if (m_clock.getElapsedTime() >= period)
		{
			m_tickRate = m_tick * (1.0 / period);
			m_tick = 0;
			reset = true;
			m_clock.restart();
		}

		m_tick++;

		return reset;
	}

	inline std::size_t getTickRate() const { return m_tickRate; }

private:
	std::size_t m_tick = 0;
	std::size_t m_tickRate = 0;
	Clock m_clock;
};

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

INTERNAL void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}
INTERNAL void render()
{
	glEnableVertexAttribArray(0); // vertPosition
	glEnableVertexAttribArray(1); // vertColor
	glEnableVertexAttribArray(2); // vertTexCoord

	glVertexAttribPointer(
	    0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(0));
	glVertexAttribPointer(1,
	                      3,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      7 * sizeof(float),
	                      (const GLvoid*)(2 * sizeof(float)));
	glVertexAttribPointer(2,
	                      2,
	                      GL_FLOAT,
	                      GL_FALSE,
	                      7 * sizeof(float),
	                      (const GLvoid*)(5 * sizeof(float)));

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	glDisableVertexAttribArray(0); // vertPosition
	glDisableVertexAttribArray(1); // vertColor
	glDisableVertexAttribArray(2); // vertTexCoord
}
INTERNAL void handleInput(GLFWwindow* window, bool* running, bool* fullscreen)
{
	if (glfwWindowShouldClose(window) || glfwGetKey(window, GLFW_KEY_ESCAPE))
		*running = false;

	/*if (glfwGetKey(window, GLFW_KEY_F11))
	{
	    *fullscreen = !(*fullscreen);

	    GLFWwindow* newWindow;

	    glfwHints();
	    if (*fullscreen)
	    {
	        int count;
	        const GLFWvidmode* modes =
	            glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

	        newWindow = glfwCreateWindow(modes[count - 1].width,
	                                     modes[count - 1].height,
	                                     "Dunjun",
	                                     glfwGetPrimaryMonitor(),
	                                     window);
	    }
	    else
	    {
	        newWindow = glfwCreateWindow(
	            g_windowWidth, g_windowHeight, "Dunjun", nullptr, window);
	    }

	    glfwDestroyWindow(window);
	    window = newWindow;
	    glfwMakeContextCurrent(window);
	}*/
}

// TODO(bill): Remove this and implement a true font render
//             Maybe using stb_truetype.h?
namespace Debug
{
// Color Helper Union
// NOTE(bill): May implement this into actual project as the Color type
union Color
{
	Dunjun::u8 rgba[4];
	struct
	{
		Dunjun::u8 r, g, b, a;
	};
};

struct stb_font_vertex
{
	Dunjun::f32 x, y, z;
	Color color;
};

INTERNAL void drawString(GLFWwindow* window,
                         const std::string& text,
                         float x,
                         float y,
                         Color color)
{
	LOCAL_PERSIST stb_font_vertex buffer[6000]; // ~500 chars
	int numQuads = stb_easy_font_print(
	    x, y, (char*)text.c_str(), nullptr, buffer, sizeof(buffer));

	glPushMatrix();
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		int width, height;
		glfwGetWindowSize(window, &width, &height);
		glOrtho(0.0f, (GLfloat)width, (GLfloat)height, 0.0f, -1.0f, 1.0f);

		glColor4ubv(color.rgba);
		glBegin(GL_QUADS);
		for (int i = 0; i < numQuads; i++)
		{
			glVertex2f(buffer[4 * i + 3].x, buffer[4 * i + 3].y);
			glVertex2f(buffer[4 * i + 2].x, buffer[4 * i + 2].y);
			glVertex2f(buffer[4 * i + 1].x, buffer[4 * i + 1].y);
			glVertex2f(buffer[4 * i + 0].x, buffer[4 * i + 0].y);
		}
		glEnd();
	}
	glPopMatrix();
}
} // namespace Debug

int main(int argc, char** argv)
{
	GLFWwindow* window;

	if (!glfwInit())
		return EXIT_FAILURE;

	glfwHints();
	window = glfwCreateWindow(
	    g_windowWidth, g_windowHeight, "Dunjun", nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return EXIT_FAILURE;
	}

	glfwMakeContextCurrent(window);

	glewInit();

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	float vertices[] = {
	    //  x      y     r     g     b     s     t
	    +0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, // Vertex 0
	    -0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // Vertex 1
	    +0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f, // Vertex 2
	    -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, // Vertex 3
	};

	GLuint vbo; // Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Dunjun::ShaderProgram shaderProgram;
	if (!shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Vertex,
	                                        "data/shaders/default.vert.glsl"))
		throw std::runtime_error(shaderProgram.getErrorLog());

	if (!shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Fragment,
	                                        "data/shaders/default.frag.glsl"))
		throw std::runtime_error(shaderProgram.getErrorLog());
	shaderProgram.bindAttribLocation(0, "vertPosition");
	shaderProgram.bindAttribLocation(1, "vertColor");
	shaderProgram.bindAttribLocation(2, "vertTexCoord");
	if (!shaderProgram.link())
		throw std::runtime_error(shaderProgram.getErrorLog());
	shaderProgram.use();

	Dunjun::Texture tex;
	tex.loadFromFile("data/textures/kitten.jpg");
	tex.bind(0);
	shaderProgram.setUniform("uniTex", 0);

	bool running = true;
	bool fullscreen = false;

	std::stringstream titleStream;

	TickCounter tc;
	Clock frameClock;

	while (running)
	{
		// reshape
		// TODO(bill): only get window size when windows is resized
		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.use();
		render();
		shaderProgram.stopUsing();

		if (tc.update(0.5))
		{
			titleStream.str("");
			titleStream.clear();
			titleStream << "Dunjun - " << 1000.0 / tc.getTickRate() << " ms";
			glfwSetWindowTitle(window, titleStream.str().c_str());
		}


		// Debug
		Debug::drawString(
		    window, titleStream.str(), 0, 0, {{255, 255, 255, 255}});

		glfwSwapBuffers(window);
		glfwPollEvents();

		handleInput(window, &running, &fullscreen);


		while (frameClock.getElapsedTime() < 1.0 / 240.0)
			;
		frameClock.restart();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
