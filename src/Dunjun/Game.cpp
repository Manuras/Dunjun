#include <Dunjun/Game.hpp>

#include <Dunjun/Common.hpp>

#include <Dunjun/Window.hpp>
#include <Dunjun/Input.hpp>

#include <Dunjun/Clock.hpp>
#include <Dunjun/TickCounter.hpp>

#include <Dunjun/Math.hpp>
#include <Dunjun/Camera.hpp>
#include <Dunjun/ModelAsset.hpp>
#include <Dunjun/Level.hpp>

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Dunjun
{
struct ModelInstance
{
	ModelAsset* asset;
	Transform transform;
};

namespace
{
GLOBAL const f32 TIME_STEP = 1.0f / 60.0f;
GLOBAL bool g_running = true;
} // namespace (anonymous)

GLOBAL ShaderProgram* g_defaultShader;
GLOBAL ModelAsset g_sprite;
GLOBAL std::vector<ModelInstance> g_instances;
GLOBAL Camera g_camera;
GLOBAL std::map<std::string, Material> g_materials;
GLOBAL std::map<std::string, Mesh*> g_meshes;

GLOBAL Level g_level;

namespace Game
{
INTERNAL void handleInput()
{
	if (Window::shouldClose() || Input::isKeyPressed(Input::Key::Escape))
		g_running = false;

	if (Input::isKeyPressed(Input::Key::F11))
	{
		Window::isFullscreen = !Window::isFullscreen;
		if (Window::isFullscreen)
		{
			GLFWwindow* w = Window::createWindow(glfwGetPrimaryMonitor());
			Window::destroyWindow();
			Window::ptr = w;
		}
		else
		{
			GLFWwindow* w = Window::createWindow(nullptr);
			Window::destroyWindow();
			Window::ptr = w;
		}

		Window::makeContextCurrent();
		Window::swapInterval(1);

		// Initial OpenGL settings
		glInit();
	}
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
	g_defaultShader->bindAttribLocation((u32)AtrribLocation::Position,
	                                    "a_position");
	g_defaultShader->bindAttribLocation((u32)AtrribLocation::TexCoord,
	                                    "a_texCoord");
	g_defaultShader->bindAttribLocation((u32)AtrribLocation::Color, "a_color");

	if (!g_defaultShader->link())
		throw std::runtime_error(g_defaultShader->errorLog);
}
INTERNAL void loadMaterials()
{
	g_materials["default"].shaders = g_defaultShader;
	g_materials["default"].texture = new Texture();
	g_materials["default"].texture->loadFromFile("data/textures/default.png");

	g_materials["cat"].shaders = g_defaultShader;
	g_materials["cat"].texture = new Texture();
	g_materials["cat"].texture->loadFromFile("data/textures/kitten.jpg");

	g_materials["stone"].shaders = g_defaultShader;
	g_materials["stone"].texture = new Texture();
	g_materials["stone"].texture->loadFromFile("data/textures/stone.png",
	                                           TextureFilter::Nearest);

	g_materials["terrain"].shaders = g_defaultShader;
	g_materials["terrain"].texture = new Texture();
	g_materials["terrain"].texture->loadFromFile("data/textures/terrain.png",
	                                             TextureFilter::Nearest);
}
INTERNAL void loadSpriteAsset()
{
	Mesh::Data meshData;
	meshData.vertices.push_back(
	    {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {{0x00, 0x00, 0xFF, 0xFF}}});
	meshData.vertices.push_back(
	    {{+0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {{0x00, 0xFF, 0x00, 0xFF}}});
	meshData.vertices.push_back(
	    {{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
	meshData.vertices.push_back(
	    {{-0.5f, +0.5f, 0.0f}, {0.0f, 1.0f}, {{0xFF, 0x00, 0x00, 0xFF}}});

	meshData.indices.push_back(0);
	meshData.indices.push_back(1);
	meshData.indices.push_back(2);
	meshData.indices.push_back(2);
	meshData.indices.push_back(3);
	meshData.indices.push_back(0);

	g_meshes["sprite"] = new Mesh(meshData);

	g_sprite.material = &g_materials["cat"];
	g_sprite.mesh = g_meshes["sprite"];
}

INTERNAL void generateWorld()
{
	g_level.material = &g_materials["terrain"];

	g_level.generate();
}


GLOBAL Matrix4 g_projTest;

INTERNAL void loadInstances()
{
	Transform parent;

	ModelInstance a;
	a.asset = &g_sprite;
	a.transform.position = {4, 1, 4};
	a.transform.scale = {1, 2, 1};
	// a.transform.orientation = angleAxis(Degree(45), {0, 0, 1});
	g_instances.push_back(a);

	generateWorld();


	g_camera.viewportAspectRatio = 16.0f / 9.0f;

	// Init Camera
	g_camera.transform.position = {4, 7, 14};

	g_camera.lookAt({4, 0, 0});
	// g_camera.projectionType = ProjectionType::Orthographic;
	// g_camera.orthoScale = 800;
	g_camera.projectionType = ProjectionType::Perspective;
	g_camera.fieldOfView = Degree(50.0f);

	const Matrix4 pp = g_camera.getProjection();

	g_camera.projectionType = ProjectionType::Orthographic;
	g_camera.orthoScale = 600;

	const Matrix4 op = g_camera.getProjection();


	g_projTest = lerp(pp, op, 0.9f);
}

INTERNAL void update(f32 dt)
{
	ModelInstance& player = g_instances[0];

	f32 camVel = 3.0f;
	{
		if (Input::isGamepadPresent(Input::Gamepad_1))
		{
			Input::GamepadAxes axes = Input::getGamepadAxes(Input::Gamepad_1);

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
			if (Input::isGamepadButtonPressed(Input::Gamepad_1,
				Input::XboxButton::A))
			{
				Input::setGamepadVibration(Input::Gamepad_1, 0.5f, 0.5f);
			}
			else
			{
				Input::setGamepadVibration(Input::Gamepad_1, 0.0f, 0.0f);
			}
		}
	}

	f32 playerVel = 4.0f;
	{
		Vector3 velDir = {0, 0, 0};

		if (Input::isKeyPressed(Input::Key::Up))
			velDir += {0, 0, -1};
		if (Input::isKeyPressed(Input::Key::Down))
			velDir += {0, 0, +1};

		if (Input::isKeyPressed(Input::Key::Left))
			velDir += {-1, 0, 0};
		if (Input::isKeyPressed(Input::Key::Right))
			velDir += {+1, 0, 0};

		if (Input::isKeyPressed(Input::Key::RShift))
			velDir += {0, +1, 0};
		if (Input::isKeyPressed(Input::Key::RControl))
			velDir += {0, -1, 0};

		if (length(velDir) > 0)
			velDir = normalize(velDir);

		{
			player.transform.position += playerVel * velDir * dt;

#if 0   // Billboard
			Quaternion pRot = conjugate(quaternionLookAt(player.transform.position,
				g_camera.transform.position,
				{0, 1, 0}));


			player.transform.orientation = pRot;
#elif 0 // Billboard fixed y-axis
			Vector3 f = player.transform.position - g_camera.transform.position;
			f.y = 0;
			if (f.x == 0 && f.z == 0)
			{
				player.transform.orientation = Quaternion();
			}
			else
			{
				Radian a(-std::atan(f.z / f.x));
				a += Radian(Constants::TAU / 4);
				if (f.x >= 0)
					a -= Radian(Constants::TAU / 2);

				player.transform.orientation = angleAxis(a, {0, 1, 0});
			}
#endif
		}
	}

	{
		f32 dx = player.transform.position.x - g_camera.transform.position.x;

		f32 dxAbs = std::abs(dx);
		f32 w = 0.5f;
		f32 speed = 3.0f;

		if (dxAbs > w)
		{
			f32 sgn = dx / dxAbs;
			f32 x = dxAbs - w;
			x = x * x;
			g_camera.transform.position.x += speed * sgn * x * dt;
		}
	}

	// g_camera.transform.position.x = player.transform.position.x;
	f32 aspectRatio =
	    Window::getFramebufferSize().x / Window::getFramebufferSize().y;
	if (aspectRatio && Window::getFramebufferSize().y > 0)
		g_camera.viewportAspectRatio = aspectRatio;


	{
		g_camera.projectionType = ProjectionType::Perspective;
		const Matrix4 pp = g_camera.getProjection();
		g_camera.projectionType = ProjectionType::Orthographic;
		const Matrix4 op = g_camera.getProjection();


		LOCAL_PERSIST f32 time = 0;
		time += dt;
		
		f32 w = 0.3f;
		f32 t = std::sin(w * time)*std::sin(w * time);

		t = std::pow(t, 0.3f);

		g_projTest = lerp(pp, op, 0.95f);
		//g_projTest = lerp(pp, op, 1.0f);

	}

}


INTERNAL void renderInstance(const ModelInstance& inst)
{
	ModelAsset* asset = inst.asset;
	ShaderProgram* shaders = asset->material->shaders;

	shaders->setUniform("u_camera", g_projTest * g_camera.getView());
	shaders->setUniform("u_transform", inst.transform);
	shaders->setUniform("u_tex", (u32)0);

	asset->mesh->draw();
}

INTERNAL void renderLevel(const Level& level)
{
	ShaderProgram* shaders = level.material->shaders;
	if (!shaders)
		return;

	shaders->setUniform("u_camera", g_projTest * g_camera.getView());
	shaders->setUniform("u_transform", level.transform);
	shaders->setUniform("u_tex", (u32)0);

	level.mesh->draw();
}

INTERNAL void render()
{
	{
		Vector2 fbSize = Window::getFramebufferSize();
		glViewport(0, 0, fbSize.x, fbSize.y);
	}
	glClearColor(0, 0, 0, 1);
	// glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	const ShaderProgram* currentShaders = nullptr;
	const Texture* currentTexture = nullptr;

	// Level
	{
		if (g_level.material->shaders != currentShaders)
		{
			if (currentShaders)
				currentShaders->stopUsing();
			currentShaders = g_level.material->shaders;
			currentShaders->use();
		}

		if (g_level.material->texture != currentTexture)
		{
			currentTexture = g_level.material->texture;

			Texture::bind(currentTexture, 0);
		}

		renderLevel(g_level);
	}
	// Instances
	for (const auto& inst : g_instances)
	{
		if (inst.asset->material->shaders != currentShaders)
		{
			if (currentShaders)
				currentShaders->stopUsing();
			currentShaders = inst.asset->material->shaders;
			currentShaders->use();
		}

		if (inst.asset->material->texture != currentTexture)
		{
			currentTexture = inst.asset->material->texture;
			Texture::bind(currentTexture, 0);
		}

		renderInstance(inst);
	}

	if (currentShaders)
		currentShaders->stopUsing();

	Texture::bind(nullptr, 0);

	Window::swapBuffers();
}

void init()
{
	if (!Window::init())
		return;

	glewInit();

	// Initial OpenGL settings
	glInit();

	Input::setup();
	Input::setCursorPosition({0, 0});
	// Input::setCursorMode(Input::CursorMode::Disabled);

	loadShaders();
	loadMaterials();
	loadSpriteAsset();
	loadInstances();
}

void run()
{
	std::stringstream titleStream;

	TickCounter tc;
	Clock frameClock;

	f64 accumulator = 0;
	f64 prevTime = Input::getTime();

	while (g_running)
	{
		// Window::pollEvents();

		Window::makeContextCurrent();

		f64 currentTime = Input::getTime();
		f64 dt = currentTime - prevTime;
		prevTime = currentTime;
		accumulator += dt;

		if (accumulator > 1.2f) // remove loop of death
			accumulator = 1.2f;

		while (accumulator >= TIME_STEP)
		{
			accumulator -= TIME_STEP;
			Window::pollEvents();
			handleInput();
			Input::updateGamepads();
			update(TIME_STEP);
		}

		if (tc.update(0.5))
		{
			titleStream.str("");
			titleStream.clear();
			titleStream << "Dunjun - " << 1000.0 / tc.getTickRate() << " ms";
			Window::setTitle(titleStream.str().c_str());
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
	Window::cleanup();
}

void glInit()
{
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
}
} // namespace Game
} // namespace Dunjun
