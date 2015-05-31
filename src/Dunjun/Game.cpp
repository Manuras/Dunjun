#include <Dunjun/Config.hpp>
#include <Dunjun/Game.hpp>

#include <Dunjun/Clock.hpp>
#include <Dunjun/Level/Level.hpp>
#include <Dunjun/ResourceHolders.hpp>
#include <Dunjun/Scene.hpp>
#include <Dunjun/TickCounter.hpp>
#include <Dunjun/Window.hpp>

#include <cassert>
#include <cstdlib>
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
GLOBAL const Time TimeStep{seconds(1.0f / 60.0f)};
GLOBAL const Time MaxFrameTime{seconds(1.0f / (288.0f + 1.0f))};

GLOBAL bool g_running{true};
} // namespace (anonymous)

GLOBAL Camera g_cameraPlayer;
GLOBAL Camera g_cameraWorld;

GLOBAL Camera* g_currentCamera{&g_cameraPlayer};

GLOBAL ModelAsset g_sprite;

GLOBAL SceneNode g_rootNode;
GLOBAL SceneNode* g_player{nullptr};

GLOBAL SceneRenderer g_renderer;

GLOBAL Level* g_level{nullptr};

GLOBAL std::vector<PointLight> g_pointLights;
GLOBAL std::vector<DirectionalLight> g_directionalLights;

namespace Game
{
INTERNAL void handleInput()
{
	if (Window::shouldClose() || Input::isKeyPressed(Input::Key::Escape))
		g_running = false;

	if (Input::isKeyPressed(Input::Key::F11))
	{
		Window::setFullscreen(!Window::isFullscreen());
		if (Window::isFullscreen())
		{
			GLFWwindow* w{Window::createWindow(glfwGetPrimaryMonitor())};
			Window::destroyWindow();
			Window::setHandle(w);
		}
		else
		{
			GLFWwindow* w{Window::createWindow()};
			Window::destroyWindow();
			Window::setHandle(w);
		}

		Window::makeContextCurrent();
		Window::swapInterval(0);

		// Initial OpenGL settings
		glInit();
	}
}

INTERNAL void loadShaders()
{
	g_shaderHolder.insertFromFile("texPass",           //
	                              "texPass.vert.glsl", //
	                              "texPass.frag.glsl");
	g_shaderHolder.insertFromFile("deferredGeometryPass",
	                              "deferredGeometryPass.vert.glsl",
	                              "deferredGeometryPass.frag.glsl");
	g_shaderHolder.insertFromFile("deferredAmbientLight",
	                              "deferredLightPass.vert.glsl",
	                              "deferredAmbientLight.frag.glsl");
	g_shaderHolder.insertFromFile("deferredPointLight",
	                              "deferredLightPass.vert.glsl",
	                              "deferredPointLight.frag.glsl");
	g_shaderHolder.insertFromFile("deferredDirectionalLight",
	                              "deferredLightPass.vert.glsl",
	                              "deferredDirectionalLight.frag.glsl");
}
INTERNAL void loadMaterials()
{
	g_textureHolder.insertFromFile("default", "default.png");
	g_textureHolder.insertFromFile("kitten", "kitten.jpg");
	g_textureHolder.insertFromFile("stone", "stone.png");
	g_textureHolder.insertFromFile("terrain", "terrain.png", //
	                               TextureFilter::Nearest);

	{
		auto mat = make_unique<Material>();
		mat->shaders = &g_shaderHolder.get("deferredGeometryPass");
		mat->diffuseMap = &g_textureHolder.get("default");
		g_materialHolder.insert("default", std::move(mat));
	}

	{
		auto mat = make_unique<Material>();
		mat->shaders = &g_shaderHolder.get("deferredGeometryPass");
		mat->diffuseMap = &g_textureHolder.get("kitten");
		mat->specularExponent = 1e5;
		g_materialHolder.insert("cat", std::move(mat));
	}

	{
		auto mat = make_unique<Material>();
		mat->shaders = &g_shaderHolder.get("deferredGeometryPass");
		mat->diffuseMap = &g_textureHolder.get("stone");
		g_materialHolder.insert("stone", std::move(mat));
	}

	{
		auto mat = make_unique<Material>();
		mat->shaders = &g_shaderHolder.get("deferredGeometryPass");
		mat->diffuseMap = &g_textureHolder.get("terrain");
		g_materialHolder.insert("terrain", std::move(mat));
	}
}
INTERNAL void loadSpriteAsset()
{
	{
		Mesh::Data meshData;
		meshData.vertices.reserve(4); // There will be 4 vertices
		meshData.vertices //
		    .append({-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f})
		    .append({+0.5f, -0.5f, 0.0f}, {1.0f, 0.0f})
		    .append({+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f})
		    .append({-0.5f, +0.5f, 0.0f}, {0.0f, 1.0f});

		meshData.indices.reserve(6);
		meshData.addFace(0, 1, 2).addFace(2, 3, 0);
		meshData.generateNormals();

		g_meshHolder.insert("sprite", make_unique<Mesh>(meshData));

		g_sprite.material = &g_materialHolder.get("cat");
		g_sprite.mesh = &g_meshHolder.get("sprite");
	}
	{
		Mesh::Data meshData;
		meshData.vertices.reserve(4); // There will be 4 vertices
		meshData.vertices //
		    .append({-1.0f, -1.0f, 0.0f}, {0.0f, 0.0f})
		    .append({+1.0f, -1.0f, 0.0f}, {1.0f, 0.0f})
		    .append({+1.0f, +1.0f, 0.0f}, {1.0f, 1.0f})
		    .append({-1.0f, +1.0f, 0.0f}, {0.0f, 1.0f});

		meshData.indices.reserve(6);
		meshData.addFace(0, 1, 2).addFace(2, 3, 0);
		meshData.generateNormals();

		g_meshHolder.insert("quad", make_unique<Mesh>(meshData));
	}
}

INTERNAL void loadInstances()
{
	g_rootNode.onStart();
	{
		auto player = make_unique<SceneNode>();

		player->name = "player";
		player->transform.position = {2, 0.5, 2};
		player->transform.orientation = angleAxis(Degree{45}, {0, 1, 0});
		player->addComponent<MeshRenderer>(g_sprite);
		player->addComponent<FaceCamera>(g_cameraWorld);

		g_player = player.get();

		g_rootNode.attachChild(std::move(player));
	}

	{
		auto level = make_unique<Level>();

		level->material = &g_materialHolder.get("terrain");
		level->generate();

		g_level = level.get();

		g_rootNode.attachChild(std::move(level));
	}

	Random random{1};
	for (int i{0}; i < 20; i++)
	{
		PointLight light;
		f32 radius{random.getFloat(0.1f, 16.0f)};
		Radian angle{random.getFloat(0, Math::Tau)};
		light.position.x = 4.0f + radius * Math::cos(angle);
		light.position.y = random.getFloat(0.5, 2.5);
		light.position.z = 4.0f + radius * Math::sin(angle);

		light.intensity = 1.0;

		light.color.r = random.getInt(50, 255);
		light.color.g = random.getInt(50, 255);
		light.color.b = random.getInt(50, 255);

		g_pointLights.emplace_back(light);
	}

	{
		DirectionalLight light;
		light.color = Color{255, 255, 250};
		light.direction = Vector3{-1, -1, 0.5};
		light.intensity = 0.1f;

		g_directionalLights.emplace_back(light);
	}

	// Init Camera
	g_cameraPlayer.transform.position = {5, 2, 5};
	g_cameraPlayer.transform.orientation =
	    angleAxis(Degree{45}, {0, 1, 0}) * angleAxis(Degree{-30}, {1, 0, 0});

	g_cameraPlayer.fieldOfView = Degree{50.0f};
	g_cameraPlayer.orthoScale = 8;

	g_cameraWorld = g_cameraPlayer;

	g_cameraPlayer.projectionType = ProjectionType::Orthographic;

	g_currentCamera = &g_cameraWorld;

	g_rootNode.onStart();
}

INTERNAL void update(Time dt)
{
	g_rootNode.update(dt);

	f32 camVel{10.0f};
	{
		if (Input::isGamepadPresent(Input::Gamepad_1))
		{
			Input::GamepadAxes axes{Input::getGamepadAxes(Input::Gamepad_1)};

			const f32 lookSensitivity{2.0f};
			const f32 deadZone{0.21f};

			Vector2 rts{axes.rightThumbstick};
			if (Math::abs(rts.x) < deadZone)
				rts.x = 0;
			if (Math::abs(rts.y) < deadZone)
				rts.y = 0;

			g_cameraWorld.offsetOrientation(
			    -lookSensitivity * Radian{rts.x * dt.asSeconds()},
			    +lookSensitivity * Radian{rts.y * dt.asSeconds()});

			Vector2 lts{axes.leftThumbstick};

			if (Math::abs(lts.x) < deadZone)
				lts.x = 0;
			if (Math::abs(lts.y) < deadZone)
				lts.y = 0;

			if (length(lts) > 1.0f)
				lts = normalize(lts);

			Vector3 velDir{0, 0, 0};

			Vector3 forward{g_cameraWorld.forward()};
			forward.y = 0;
			forward = normalize(forward);
			velDir += lts.x * g_cameraWorld.right();
			velDir += lts.y * forward;

			Input::GamepadButtons buttons{
			    Input::getGamepadButtons(Input::Gamepad_1)};

			if (buttons[(usize)Input::XboxButton::RightShoulder])
				velDir.y += 1;
			if (buttons[(usize)Input::XboxButton::LeftShoulder])
				velDir.y -= 1;

			if (buttons[(usize)Input::XboxButton::DpadUp])
			{
				Vector3 f{g_cameraWorld.forward()};
				f.y = 0;
				f = normalize(f);
				velDir += f;
			}
			if (buttons[(usize)Input::XboxButton::DpadDown])
			{
				Vector3 b{g_cameraWorld.backward()};
				b.y = 0;
				b = normalize(b);
				velDir += b;
			}

			if (buttons[(usize)Input::XboxButton::DpadLeft])
			{
				Vector3 l{g_cameraWorld.left()};
				l.y = 0;
				l = normalize(l);
				velDir += l;
			}
			if (buttons[(usize)Input::XboxButton::DpadRight])
			{
				Vector3 r{g_cameraWorld.right()};
				r.y = 0;
				r = normalize(r);
				velDir += r;
			}

			if (length(velDir) > 1.0f)
				velDir = normalize(velDir);

			g_cameraWorld.transform.position +=
			    camVel * velDir * dt.asSeconds();

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

	f32 playerVel{4.0f};
	{
		Vector3 velDir{0, 0, 0};

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
			g_player->transform.position += playerVel * velDir * dt.asSeconds();

#if 0   // Billboard
			Quaternion pRot{conjugate(quaternionLookAt(player.transform.position,
				g_camera.transform.position,
				{0, 1, 0}))};


			player.transform.orientation = pRot;
#elif 0 // Billboard fixed y-axis
			Vector3 f{player.transform.position - g_camera.transform.position};
			f.y = 0;
			if (f.x == 0 && f.z == 0)
			{
				player.transform.orientation = Quaternion();
			}
			else
			{
				Radian a{-Math::atan(f.z / f.x)};
				a += Radian(Constants::Tau / 4);
				if (f.x >= 0)
					a -= Radian(Constants::Tau / 2);

				player.transform.orientation = angleAxis(a, {0, 1, 0});
			}
#endif
		}
	}

	g_cameraPlayer.transform.position.x =
	    Math::lerp(g_cameraPlayer.transform.position.x,
	               g_player->transform.position.x,
	               10.0f * dt.asSeconds());
	g_cameraPlayer.transform.position.z =
	    Math::lerp(g_cameraPlayer.transform.position.z,
	               g_player->transform.position.z,
	               10.0f * dt.asSeconds());

	// g_camera.transform.position.x = player.transform.position.x;
	f32 aspectRatio{Window::getFramebufferSize().aspectRatio()};
	if (aspectRatio && Window::getFramebufferSize().height > 0)
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

#if 1
	// TODO(bill): Make bounding boxes for SceneNodes and implement this
	// in SceneRenderer
	for (auto& room : g_level->rooms)
	{
		Vector3 roomPos{room->transform.position};
		roomPos.x += room->size.x / 2;
		roomPos.z += room->size.y / 2;
		const Vector3 playerPos{g_cameraWorld.transform.position};

		const Vector3 dp{roomPos - playerPos};

		const f32 dist{length(dp)};

		// Distance Culling
		if (dist < g_cameraWorld.farPlane)
		{
			const Vector3 f{g_cameraWorld.forward()};

			f32 cosTheta{dot(f, normalize(dp))};

			Radian theta{Math::acos(cosTheta)};

			// Cone/(bad) Frustum Culling
			if (Math::abs(theta) <= 2.0f * g_cameraWorld.fieldOfView ||
			    dist < 10)
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
	Window::Dimensions fbSize = Window::getFramebufferSize();

	g_renderer.reset();
	g_renderer.clearAll();
	g_renderer.addSceneGraph(g_rootNode);

	for (const auto& light : g_pointLights)
		g_renderer.addPointLight(&light);
	for (const auto& light : g_directionalLights)
		g_renderer.addDirectionalLight(&light);

	g_renderer.camera = g_currentCamera;

	g_renderer.gBuffer.create(fbSize.width, fbSize.height);

	g_renderer.geometryPass();
	g_renderer.lightPass();

	// g_materialHolder.get("cat").diffuseMap =
	//     &g_renderer.lightingTexture.colorTexture;

	glViewport(0, 0, fbSize.width, fbSize.height);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{
		ShaderProgram& shaders = g_shaderHolder.get("texPass");
		shaders.use();

		shaders.setUniform("u_scale", Vector3{1.0f});
		shaders.setUniform("u_tex", 0);
		Texture::bind(&g_renderer.lightingTexture.colorTexture, 0);

		g_renderer.draw(&g_meshHolder.get("quad"));

		shaders.stopUsing();
	}
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
	TickCounter tc;
	Clock frameClock;

	Time accumulator;
	Time prevTime{Time::now()};

	Window::makeContextCurrent();

	while (g_running)
	{
		// Window::pollEvents();

		Time currentTime{Time::now()};
		Time dt{currentTime - prevTime};
		prevTime = currentTime;
		accumulator += dt;

		if (accumulator > milliseconds(1200)) // remove loop of death
			accumulator = milliseconds(1200);

		while (accumulator >= TimeStep)
		{
			accumulator -= TimeStep;
			Window::pollEvents();
			handleInput();
			Input::updateGamepads();
			update(TimeStep);
		}

		// Set Window Title
		if (tc.update(milliseconds(500)))
		{
			Window::setTitle(
				stringFormat("Dunjun - %.3f ms - %d fps",
				             1000.0f / tc.getTickRate(),
				             (u32)tc.getTickRate()));
		}

		render();

		// Frame Limiter
		const Time framelimitTime{MaxFrameTime - frameClock.getElapsedTime()};
		if (framelimitTime > Time::Zero)
			Time::sleep(framelimitTime);
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
