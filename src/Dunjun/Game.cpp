#include <Dunjun/Game.hpp>

#include <Dunjun/Common.hpp>

#include <Dunjun/Window.hpp>
#include <Dunjun/Input.hpp>

#include <Dunjun/RenderTexture.hpp>
#include <Dunjun/GBuffer.hpp>


#include <Dunjun/Clock.hpp>
#include <Dunjun/TickCounter.hpp>

#include <Dunjun/Math.hpp>
#include <Dunjun/Camera.hpp>
#include <Dunjun/ModelAsset.hpp>

#include <Dunjun/Scene.hpp>

#include <Dunjun/Level/Level.hpp>

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
GLOBAL const f32 TimeStep = 1.0f / 60.0f;
GLOBAL bool g_running = true;
} // namespace (anonymous)

GLOBAL Camera g_cameraPlayer;
GLOBAL Camera g_cameraWorld;

GLOBAL Camera* g_currentCamera = &g_cameraPlayer;

GLOBAL ShaderProgram* g_defaultShader;
GLOBAL ShaderProgram* g_texPassShader;

GLOBAL ModelAsset g_sprite;

GLOBAL SceneNode g_rootNode;
GLOBAL SceneNode* g_player;

GLOBAL SceneRenderer g_renderer;

GLOBAL std::map<std::string, Material> g_materials;
GLOBAL std::map<std::string, Mesh*> g_meshes;

GLOBAL Level* g_level;

GLOBAL PointLight g_light;

namespace Game
{
INTERNAL void handleInput()
{
	if (Window::shouldClose() || Input::isKeyPressed(Input::Key::Escape))
		g_running = false;

	if (Input::isKeyPressed(Input::Key::F11))
	{
		Window::g_isFullscreen = !Window::g_isFullscreen;
		if (Window::g_isFullscreen)
		{
			GLFWwindow* w = Window::createWindow(glfwGetPrimaryMonitor());
			Window::destroyWindow();
			Window::g_ptr = w;
		}
		else
		{
			GLFWwindow* w = Window::createWindow(nullptr);
			Window::destroyWindow();
			Window::g_ptr = w;
		}

		Window::makeContextCurrent();
		Window::swapInterval(1);

		// Initial OpenGL settings
		glInit();
	}
}

INTERNAL void loadShaders()
{
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
		g_defaultShader->bindAttribLocation((u32)AtrribLocation::Normal,
											"a_normal");

		if (!g_defaultShader->link())
			throw std::runtime_error(g_defaultShader->errorLog);
	}
	{
		g_texPassShader = new ShaderProgram();
		if (!g_texPassShader->attachShaderFromFile(
		        ShaderType::Vertex, "data/shaders/texPass.vert.glsl"))
			throw std::runtime_error(g_texPassShader->errorLog);

		if (!g_texPassShader->attachShaderFromFile(
		        ShaderType::Fragment, "data/shaders/texPass.frag.glsl"))
			throw std::runtime_error(g_texPassShader->errorLog);
		g_texPassShader->bindAttribLocation((u32)AtrribLocation::Position,
		                                    "a_position");
		g_texPassShader->bindAttribLocation((u32)AtrribLocation::TexCoord,
		                                    "a_texCoord");

		if (!g_texPassShader->link())
			throw std::runtime_error(g_texPassShader->errorLog);
	}
}
INTERNAL void loadMaterials()
{
	g_materials["default"].shaders = g_defaultShader;
	g_materials["default"].diffuseMap = new Texture();
	g_materials["default"].diffuseMap->loadFromFile(
	    "data/textures/default.png");

	g_materials["cat"].shaders = g_defaultShader;
	g_materials["cat"].diffuseMap = new Texture();
	g_materials["cat"].diffuseMap->loadFromFile("data/textures/kitten.jpg");
	g_materials["cat"].specularExponent = 100000;

	g_materials["stone"].shaders = g_defaultShader;
	g_materials["stone"].diffuseMap = new Texture();
	g_materials["stone"].diffuseMap->loadFromFile("data/textures/stone.png",
	                                              TextureFilter::Nearest);

	g_materials["terrain"].shaders = g_defaultShader;
	g_materials["terrain"].diffuseMap = new Texture();
	g_materials["terrain"].diffuseMap->loadFromFile("data/textures/terrain.png",
	                                                TextureFilter::Nearest);
}
INTERNAL void loadSpriteAsset()
{
	Mesh::Data meshData;
	meshData.vertices.append({-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f})
	    .append({+0.5f, -0.5f, 0.0f}, {1.0f, 0.0f})
	    .append({+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f})
	    .append({-0.5f, +0.5f, 0.0f}, {0.0f, 1.0f});

	meshData.addFace(0, 1, 2).addFace(2, 3, 0);
	meshData.generateNormals();

	g_meshes["sprite"] = new Mesh(meshData);

	g_sprite.material = &g_materials["cat"];
	g_sprite.mesh = g_meshes["sprite"];
}

INTERNAL void generateWorld() { g_rootNode.onStart(); }

INTERNAL void loadInstances()
{
	generateWorld();

	{
		auto player = make_unique<SceneNode>();

		player->name = "player";
		player->transform.position = {2, 0.5, 2};
		player->transform.orientation = angleAxis(Degree(45), {0, 1, 0});
		player->addComponent<MeshRenderer>(g_sprite);
		// player->addComponent<FaceCamera>(g_cameraWorld);

		g_player = player.get();

		g_rootNode.attachChild(std::move(player));
	}

	{
		auto level = make_unique<Level>();

		level->material = &g_materials["terrain"];
		level->generate();

		g_level = level.get();

		g_rootNode.attachChild(std::move(level));
	}

	g_light.position = {4, 1.5, 4};
	g_light.brightness = 10.0f;
	g_light.calculateRange();

	// Init Camera
	g_cameraPlayer.transform.position = {5, 2, 5};
	g_cameraPlayer.transform.orientation =
	    angleAxis(Degree(45), {0, 1, 0}) * angleAxis(Degree(-30), {1, 0, 0});

	g_cameraPlayer.fieldOfView = Degree(50.0f);
	g_cameraPlayer.orthoScale = 8;

	g_cameraWorld = g_cameraPlayer;

	g_cameraPlayer.projectionType = ProjectionType::Orthographic;

	g_currentCamera = &g_cameraWorld;

	g_rootNode.onStart();
}

INTERNAL void update(f32 dt)
{
	g_rootNode.update(dt);

	f32 camVel = 10.0f;
	{
		if (Input::isGamepadPresent(Input::Gamepad_1))
		{
			Input::GamepadAxes axes = Input::getGamepadAxes(Input::Gamepad_1);

			const f32 lookSensitivity = 2.0f;
			const f32 deadZone = 0.21f;

			Vector2 rts = axes.rightThumbstick;
			if (Math::abs(rts.x) < deadZone)
				rts.x = 0;
			if (Math::abs(rts.y) < deadZone)
				rts.y = 0;

			g_cameraWorld.offsetOrientation(
			    -lookSensitivity * Radian(rts.x * dt),
			    lookSensitivity * Radian(rts.y * dt));

			Vector2 lts = axes.leftThumbstick;

			if (Math::abs(lts.x) < deadZone)
				lts.x = 0;
			if (Math::abs(lts.y) < deadZone)
				lts.y = 0;

			if (length(lts) > 1.0f)
				lts = normalize(lts);

			Vector3 velDir = {0, 0, 0};

			Vector3 forward = g_cameraWorld.forward();
			forward.y = 0;
			forward = normalize(forward);
			velDir += lts.x * g_cameraWorld.right();
			velDir += lts.y * forward;

			Input::GamepadButtons buttons =
			    Input::getGamepadButtons(Input::Gamepad_1);

			if (buttons[(usize)Input::XboxButton::RightShoulder])
				velDir.y += 1;
			if (buttons[(usize)Input::XboxButton::LeftShoulder])
				velDir.y -= 1;

			if (buttons[(usize)Input::XboxButton::DpadUp])
			{
				Vector3 f = g_cameraWorld.forward();
				f.y = 0;
				f = normalize(f);
				velDir += f;
			}
			if (buttons[(usize)Input::XboxButton::DpadDown])
			{
				Vector3 b = g_cameraWorld.backward();
				b.y = 0;
				b = normalize(b);
				velDir += b;
			}

			if (buttons[(usize)Input::XboxButton::DpadLeft])
			{
				Vector3 l = g_cameraWorld.left();
				l.y = 0;
				l = normalize(l);
				velDir += l;
			}
			if (buttons[(usize)Input::XboxButton::DpadRight])
			{
				Vector3 r = g_cameraWorld.right();
				r.y = 0;
				r = normalize(r);
				velDir += r;
			}

			if (length(velDir) > 1.0f)
				velDir = normalize(velDir);

			g_cameraWorld.transform.position += camVel * velDir * dt;

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
			g_player->transform.position += playerVel * velDir * dt;

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
				Radian a = -Math::atan(f.z / f.x);
				a += Radian(Constants::Tau / 4);
				if (f.x >= 0)
					a -= Radian(Constants::Tau / 2);

				player.transform.orientation = angleAxis(a, {0, 1, 0});
			}
#endif
		}
	}

	g_light.position.x =
	    4.0f + 1.0f * Math::cos(1.0f * Radian(Input::getTime()));
	g_light.position.y = 0.5f;
	g_light.position.z =
	    4.0f + 1.0f * Math::sin(1.0f * Radian(Input::getTime()));

	g_cameraPlayer.transform.position.x =
	    Math::lerp(g_cameraPlayer.transform.position.x,
	               g_player->transform.position.x,
	               10.0f * dt);
	g_cameraPlayer.transform.position.z =
	    Math::lerp(g_cameraPlayer.transform.position.z,
	               g_player->transform.position.z,
	               10.0f * dt);

	// g_camera.transform.position.x = player.transform.position.x;
	f32 aspectRatio =
	    Window::getFramebufferSize().x / Window::getFramebufferSize().y;
	if (aspectRatio && Window::getFramebufferSize().y > 0)
	{
		g_cameraPlayer.viewportAspectRatio = aspectRatio;
		g_cameraWorld.viewportAspectRatio = aspectRatio;
	}

	if (Input::isKeyPressed(Input::Key::Num1))
		g_currentCamera = &g_cameraPlayer;
	else if (Input::isKeyPressed(Input::Key::Num2))
	{
		g_cameraWorld.transform = g_cameraPlayer.transform;
		g_currentCamera = &g_cameraWorld;
	}

#if 0
	for (auto& room : g_level->rooms)
	{
		Vector3 roomPos = room->transform.position;
		roomPos.x += room->size.x / 2;
		roomPos.z += room->size.y / 2;
		const Vector3 playerPos = g_cameraWorld.transform.position;

		const Vector3 dp = roomPos - playerPos;

		const f32 dist = length(dp);

		// Distance Culling
		if (dist < 50)
		{
			const Vector3 f = g_cameraWorld.forward();

			f32 cosTheta = dot(f, normalize(dp));

			Radian theta = Math::acos(cosTheta);

			// Cone/(bad) Frustum Culling
			if (Math::abs(theta) <= 1.1f * g_cameraWorld.fieldOfView || dist < 10)
				room->visible = true;
			else
				room->visible = false;
		}
		else
			room->visible = false;
	}
#endif
}

INTERNAL void render()
{
	LOCAL_PERSIST RenderTexture* rt = new RenderTexture();
	LOCAL_PERSIST GBuffer* gb = new GBuffer();


	g_renderer.reset();
	g_renderer.clearAll();
	g_renderer.addSceneGraph(g_rootNode);
	g_renderer.addPointLight(&g_light);
	g_renderer.currentCamera = g_currentCamera;

	Vector2 fbSize = Window::getFramebufferSize();

	rt->create(fbSize.x, fbSize.y);
	RenderTexture::bind(rt);
	{
		glViewport(0, 0, rt->width, rt->height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_renderer.renderAll();

		glFlush();
	}
	RenderTexture::unbind(rt);
	g_renderer.reset();
	g_renderer.currentCamera = g_currentCamera;

	gb->create(fbSize.x, fbSize.y);
	GBuffer::bind(gb);
	{
		glViewport(0, 0, rt->width, rt->height);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		g_renderer.renderAll();

		glFlush();
	}
	GBuffer::unbind(gb);




	g_materials["cat"].diffuseMap = &gb->diffuse;

	glViewport(0, 0, (GLsizei)fbSize.x, (GLsizei)fbSize.y);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	g_texPassShader->use();
	g_texPassShader->setUniform("u_tex", 0);
	g_texPassShader->setUniform("u_scale", Vector3(2.0f));

	Texture::bind(&rt->colorTexture, 0);

	g_renderer.draw(g_meshes["sprite"]);

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

		while (accumulator >= TimeStep)
		{
			accumulator -= TimeStep;
			Window::pollEvents();
			handleInput();
			Input::updateGamepads();
			update(TimeStep);
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
