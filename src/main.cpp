#include <Dunjun/Common.hpp>
#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Image.hpp>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>

GLOBAL const int g_windowWidth = 854;
GLOBAL const int g_windowHeight = 480;

INTERNAL void glfwHints()
{
	glfwWindowHint(GLFW_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_VERSION_MINOR, 1);
}

int main(int argc, char** argv)
{
	GLFWwindow* window;

	if (!glfwInit())
		return EXIT_FAILURE;


	glfwHints();
	window = glfwCreateWindow(g_windowWidth, g_windowHeight, "Dunjun", nullptr,
	                          nullptr);
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
	//      x      y     r     g     b     s     t
		+0.5f, +0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, // Vertex 0
		-0.5f, +0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, // Vertex 1
		+0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f,// Vertex 2
		-0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f,// Vertex 3
	};

	GLuint vbo; // Vertex Buffer Object
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	Dunjun::ShaderProgram shaderProgram;
	shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Vertex, 
									   "data/shaders/default.vert.glsl");
	shaderProgram.attachShaderFromFile(Dunjun::ShaderType::Fragment,
									   "data/shaders/default.frag.glsl");
	shaderProgram.bindAttribLocation(0, "vertPosition");
	shaderProgram.bindAttribLocation(1, "vertColor");
	shaderProgram.bindAttribLocation(2, "vertTexCoord");
	shaderProgram.link();
	shaderProgram.use();

	GLuint tex;
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	Dunjun::Image image;
	image.loadFromFile("data/textures/kitten.jpg");

	// Checkerboard pattern
	float pixels[] = {
		0, 0, 1,    1, 0, 0,
		0, 1, 0,    1, 1, 0,
	};
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image.width(), image.height(), 0, GL_RGB, GL_UNSIGNED_BYTE, image.pixelPtr());

	glActiveTexture(GL_TEXTURE0);
	shaderProgram.setUniform("uniTex", 0);


	bool running = true;
	bool fullscreen = false;
	while (running)
	{
		{
			int width, height;
			glfwGetWindowSize(window, &width, &height);
			glViewport(0, 0, width, height);
		}

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw Things
		{
			glEnableVertexAttribArray(0); // vertPosition
			glEnableVertexAttribArray(1); // vertColor
			glEnableVertexAttribArray(2); // vertTexCoord


			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)0);
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(2 * sizeof(float)));
			glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (const GLvoid*)(5 * sizeof(float)));


			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			glDisableVertexAttribArray(0); // vertPosition
			glDisableVertexAttribArray(1); // vertColor
			glDisableVertexAttribArray(2); // vertTexCoord

		}


		glfwSwapBuffers(window);
		glfwPollEvents();

		if (glfwWindowShouldClose(window) ||
		    glfwGetKey(window, GLFW_KEY_ESCAPE))
			running = false;

		if (glfwGetKey(window, GLFW_KEY_F11))
		{
			fullscreen = !fullscreen;

			GLFWwindow* newWindow;

			glfwHints();
			if (fullscreen)
			{
				int count;
				const GLFWvidmode* modes =
				    glfwGetVideoModes(glfwGetPrimaryMonitor(), &count);

				newWindow = glfwCreateWindow(modes[count - 1].width,
				                             modes[count - 1].height, "Dunjun",
				                             glfwGetPrimaryMonitor(), window);
			}
			else
			{
				newWindow = glfwCreateWindow(g_windowWidth, g_windowHeight,
				                             "Dunjun", nullptr, window);
			}

			glfwDestroyWindow(window);
			window = newWindow;
			glfwMakeContextCurrent(window);
		}
	}

	glfwDestroyWindow(window);
	glfwTerminate();
	return EXIT_SUCCESS;
}
