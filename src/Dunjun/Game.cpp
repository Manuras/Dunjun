#include <Dunjun/Game.hpp>

#include <Dunjun/OpenGL.hpp>
#include <Dunjun/Common.hpp>
#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Image.hpp>
#include <Dunjun/Texture.hpp>

#include <Dunjun/Input.hpp>

#include <Dunjun/Clock.hpp>
#include <Dunjun/TickCounter.hpp>

#include <Dunjun/Vertex.hpp>
#include <Dunjun/Math.hpp>
#include <Dunjun/Transform.hpp>
#include <Dunjun/Camera.hpp>

#include <GLFW/glfw3.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Dunjun
{
struct ModelAsset
{
	ShaderProgram* shaders;
	Texture* texture;

	GLuint vbo;
	GLuint ibo;

	GLenum drawType;
	GLint drawCount;
};

struct ModelInstance
{
	ModelAsset* asset;
	Transform transform;
};

namespace
{
	const f32 TIME_STEP = 1.0f / 60.0f;
	GLFWwindow* window;
	int windowWidth = 854;
	int windowHeight = 480;
} // namespace (anonymous)

GLOBAL ShaderProgram* g_defaultShader;
GLOBAL ModelAsset g_sprite;
GLOBAL std::vector<ModelInstance> g_instances;
GLOBAL Camera g_camera;

namespace Game
{
	INTERNAL void glfwHints()
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_VERSION_MINOR, 1);
		glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);
	}

	INTERNAL void resizeCallback(GLFWwindow* window, int width, int height)
	{
		windowWidth = width;
		windowHeight = height;
	}

	INTERNAL void handleInput(bool* running, bool* fullscreen)
	{
		if (glfwWindowShouldClose(window) || Input::isKeyPressed(Input::Key::Escape))
			*running = false;

		// TODO(bill): Keep context when recreating display
		//             !Fullscreen toggle!
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

	INTERNAL void loadShaders()
	{
		g_defaultShader = new ShaderProgram();
		if (!g_defaultShader->attachShaderFromFile(
		        ShaderType::Vertex, "data/shaders/default.vert.glsl"))
			throw std::runtime_error(g_defaultShader->errorLog);

		if (!g_defaultShader->attachShaderFromFile(
		        ShaderType::Fragment, "data/shaders/default.frag.glsl"))
			throw std::runtime_error(g_defaultShader->errorLog);
		g_defaultShader->bindAttribLocation(0, "a_position");
		g_defaultShader->bindAttribLocation(1, "a_color");
		g_defaultShader->bindAttribLocation(2, "a_texCoord");
		if (!g_defaultShader->link())
			throw std::runtime_error(g_defaultShader->errorLog);
	}

	INTERNAL void loadSpriteAsset()
	{
		Vertex vertices[] = {
		    //    x      y     z        r     g     b     a        s     t
		    {{-0.5f, -0.5f, 0.0f}, {{0x00, 0x00, 0xFF, 0xFF}}, {0.0f, 0.0f}},
		    {{+0.5f, -0.5f, 0.0f}, {{0x00, 0xFF, 0x00, 0xFF}}, {1.0f, 0.0f}},
		    {{+0.5f, +0.5f, 0.0f}, {{0xFF, 0xFF, 0xFF, 0xFF}}, {1.0f, 1.0f}},
		    {{-0.5f, +0.5f, 0.0f}, {{0xFF, 0x00, 0x00, 0xFF}}, {0.0f, 1.0f}},
		};

		glGenBuffers(1, &g_sprite.vbo);
		glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
		glBufferData(
		    GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		u32 indices[] = {0, 1, 2, 2, 3, 0};

		glGenBuffers(1, &g_sprite.ibo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);
		glBufferData(
		    GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		g_sprite.shaders = g_defaultShader;
		g_sprite.texture = new Texture();
		g_sprite.texture->loadFromFile("data/textures/kitten.jpg");

		g_sprite.drawType = GL_TRIANGLES;
		g_sprite.drawCount = 6;
	}

	INTERNAL void loadInstances()
	{
		Transform parent;

		ModelInstance a;
		a.asset = &g_sprite;
		a.transform.position = {0, 0, 0};
		a.transform.scale = {3, 3, 3};
		a.transform.orientation = angleAxis(Degree(45), {0, 0, 1});
		g_instances.push_back(a);

		ModelInstance b;
		b.asset = &g_sprite;
		b.transform.position = {2, 0, -0.1f};
		g_instances.push_back(b);

		ModelInstance c;
		c.asset = &g_sprite;
		c.transform.position = {0, 0, 1};
		c.transform.orientation = angleAxis(Degree(45), {0, 1, 0});
		g_instances.push_back(c);

		// Init Camera
		g_camera.transform.position = {2, 0, 7};

		g_camera.lookAt({0, 0, 0});
		g_camera.projectionType = ProjectionType::Perspective;
		g_camera.fieldOfView = Degree(50.0f);
	}

	INTERNAL void update(f32 dt)
	{
		f32 camVel = 3.0f;

		{
			if (Input::isGamepadPresent(Input::Gamepad_1))
			{
				Input::GamepadAxes axes =
				    Input::getGamepadAxes(Input::Gamepad_1);

				const f32 lookSensitivity = 2.0f;
				const f32 deadZone = 0.21f;

				Vector2 rts = axes.rightThumbstick;
				if (std::abs(rts.x) < deadZone)
					rts.x = 0;
				if (std::abs(rts.y) < deadZone)
					rts.y = 0;

				g_camera.offsetOrientation(-lookSensitivity * Radian(rts.x * dt),
				                            lookSensitivity * Radian(rts.y * dt));

				Vector2 lts = axes.leftThumbstick;

				if (std::abs(lts.x) < deadZone)
					lts.x = 0;
				if (std::abs(lts.y) < deadZone)
					lts.y = 0;

				if (length(lts) > 1.0f)
					lts = normalize(lts);

				Vector3 velDir = {0, 0, 0};

				Vector3 forward = g_camera.forward();
				forward.y = 0;
				forward = normalize(forward);
				velDir += lts.x * g_camera.right();
				velDir += lts.y * forward;

				Input::GamepadButtons buttons =
				    Input::getGamepadButtons(Input::Gamepad_1);

				if (buttons[(usize)Input::XboxButton::RightShoulder])
					velDir.y += 1;
				if (buttons[(usize)Input::XboxButton::LeftShoulder])
					velDir.y -= 1;


				if (buttons[(usize)Input::XboxButton::DpadUp])
				{
					Vector3 f = g_camera.forward();
					f.y = 0;
					f = normalize(f);
					velDir += f;
				}
				if (buttons[(usize)Input::XboxButton::DpadDown])
				{
					Vector3 b = g_camera.backward();
					b.y = 0;
					b = normalize(b);
					velDir += b;
				}


				if (buttons[(usize)Input::XboxButton::DpadLeft])
				{
					Vector3 l = g_camera.left();
					l.y = 0;
					l = normalize(l);
					velDir += l;
				}
				if (buttons[(usize)Input::XboxButton::DpadRight])
				{
					Vector3 r = g_camera.right();
					r.y = 0;
					r = normalize(r);
					velDir += r;
				}


				if (length(velDir) > 1.0f)
					velDir = normalize(velDir);

				g_camera.transform.position += camVel * velDir * dt;

				// Vibrate
				if (Input::isGamepadButtonPressed(Input::Gamepad_1, Input::XboxButton::A))
				{
					Input::setGamepadVibration(Input::Gamepad_1, 0.5f, 0.5f);
				}
				else
				{
					Input::setGamepadVibration(Input::Gamepad_1, 0.0f, 0.0f);
				}

			}
		}

		{
			Vector2 curPos = Input::getCursorPosition();

			const f32 mouseSensitivity = 0.05f;

			g_camera.offsetOrientation(-mouseSensitivity * Radian(curPos.x * dt),
			                           -mouseSensitivity * Radian(curPos.y * dt));

			Input::setCursorPosition({0, 0});

			Vector3& camPos = g_camera.transform.position;

			Vector3 velDir = {0, 0, 0};

			if (Input::isKeyPressed(Input::Key::Up))
			{
				Vector3 f = g_camera.forward();
				f.y = 0;
				f = normalize(f);
				velDir += f;
			}
			if (Input::isKeyPressed(Input::Key::Down))
			{
				Vector3 b = g_camera.backward();
				b.y = 0;
				b = normalize(b);
				velDir += b;
			}

			if (Input::isKeyPressed(Input::Key::Left))
				velDir += g_camera.left();
			if (Input::isKeyPressed(Input::Key::Right))
				velDir += g_camera.right();

			if (Input::isKeyPressed(Input::Key::RShift))
				velDir += {0, +1, 0};
			if (Input::isKeyPressed(Input::Key::RControl))
				velDir += {0, -1, 0};

			if (length(velDir) > 0)
				velDir = normalize(velDir);

			camPos += camVel * velDir * dt;

			g_camera.viewportAspectRatio =
			    getWindowSize().x / getWindowSize().y;

		/*	std::cout << Input::getScrollOffset() << std::endl;

			g_camera.fieldOfView =
			    Radian(static_cast<f32>(g_camera.fieldOfView) +
			           Input::getScrollOffset().y);*/
		}


		//g_camera.lookAt({0, 0, 0});
	}

	INTERNAL void renderInstance(const ModelInstance& inst)
	{
		ModelAsset* asset = inst.asset;
		ShaderProgram* shaders = asset->shaders;

		shaders->setUniform("u_camera", g_camera.getMatrix());
		shaders->setUniform("u_transform", inst.transform);
		shaders->setUniform("u_tex", (u32)0);

		asset->texture->bind(0);

		glBindBuffer(GL_ARRAY_BUFFER, g_sprite.vbo);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_sprite.ibo);

		glEnableVertexAttribArray(0); // vertPosition
		glEnableVertexAttribArray(1); // vertColor
		glEnableVertexAttribArray(2); // vertTexCoord

		glVertexAttribPointer(0,
		                      2,
		                      GL_FLOAT,
		                      GL_FALSE,
		                      sizeof(Vertex), // Stride
		                      (const GLvoid*)(0));
		glVertexAttribPointer(1,
		                      4,
		                      GL_UNSIGNED_BYTE, // 0-255 => 0-1
		                      GL_TRUE,
		                      sizeof(Vertex), // Stride
		                      (const GLvoid*)(sizeof(Vector3)));
		glVertexAttribPointer(2,
		                      2,
		                      GL_FLOAT,
		                      GL_FALSE,
		                      sizeof(Vertex), // Stride
		                      (const GLvoid*)(sizeof(Vector3) + sizeof(Color)));

		glDrawElements(
		    asset->drawType, asset->drawCount, GL_UNSIGNED_INT, nullptr);

		glDisableVertexAttribArray(0); // vertPosition
		glDisableVertexAttribArray(1); // vertColor
		glDisableVertexAttribArray(2); // vertTexCoord
	}

	INTERNAL void render()
	{
		glViewport(0, 0, windowWidth, windowHeight);

		glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		ShaderProgram* currentShaders = nullptr;

		for (const auto& inst : g_instances)
		{
			if (inst.asset->shaders != currentShaders)
			{
				if (currentShaders)
					currentShaders->stopUsing();
				currentShaders = inst.asset->shaders;
				currentShaders->use();
			}
			renderInstance(inst);
		}

		if (currentShaders)
			currentShaders->stopUsing();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void init()
	{
		if (!glfwInit())
			return;

		glfwHints();
		window = glfwCreateWindow(
		    windowWidth, windowHeight, "Dunjun", nullptr, nullptr);
		if (!window)
		{
			glfwTerminate();
			return;
		}

		glfwSetWindowSizeCallback(window, resizeCallback);

		glfwMakeContextCurrent(window);
		glfwSwapInterval(1);

		glewInit();

		Input::setup();

		Input::setCursorPosition({0, 0});
		Input::setCursorMode(Input::CursorMode::Disabled);

		// glEnable(GL_CULL_FACE);
		// glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);

		loadShaders();
		loadSpriteAsset();
		loadInstances();
	}

	void run()
	{
		bool running = true;
		bool fullscreen = false;

		std::stringstream titleStream;

		TickCounter tc;
		Clock frameClock;

		f64 accumulator = 0;
		f64 prevTime = Input::getTime();

		while (running)
		{
			f64 currentTime = Input::getTime();
			f64 dt = currentTime - prevTime;
			prevTime = currentTime;
			accumulator += dt;

			while (accumulator >= TIME_STEP)
			{
				accumulator -= TIME_STEP;
				handleInput(&running, &fullscreen);
				Input::updateGamepads();
				update(TIME_STEP);
			}

			if (tc.update(0.5))
			{
				titleStream.str("");
				titleStream.clear();
				titleStream << "Dunjun - " << 1000.0 / tc.getTickRate()
				            << " ms";
				glfwSetWindowTitle(window, titleStream.str().c_str());
			}

			render();

			// Frame Limiter
			while (frameClock.getElapsedTime() < 1.0 / 240.0)
				;
			frameClock.restart();
		}
	}

	void cleanup()
	{
		Input::cleanup();
		glfwDestroyWindow(window);
		glfwTerminate();
	}

	GLFWwindow* getGlfwWindow() { return window; }

	Vector2 getWindowSize() { return Vector2(windowWidth, windowHeight); }
} // namespace Game
} // namespace Dunjun
