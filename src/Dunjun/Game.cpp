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
#include <Dunjun/Mesh.hpp>

#include <GLFW/glfw3.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace Dunjun
{
struct Material
{
	ShaderProgram* shaders;
	Texture* texture;
};

struct ModelAsset
{
	const Material* material;
	const Mesh* mesh;
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
GLOBAL std::map<std::string, Material> g_materials;
GLOBAL std::map<std::string, Mesh*> g_meshes;

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
		g_defaultShader->bindAttribLocation((u32)AtrribLocation::Position, "a_position");
		g_defaultShader->bindAttribLocation((u32)AtrribLocation::TexCoord, "a_texCoord");
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
		g_materials["stone"].texture->loadFromFile("data/textures/stone.png", TextureFilter::Nearest);

		g_materials["terrain"].shaders = g_defaultShader;
		g_materials["terrain"].texture = new Texture();
		g_materials["terrain"].texture->loadFromFile("data/textures/terrain.png", TextureFilter::Nearest);
	}

	INTERNAL void loadSpriteAsset()
	{
		Mesh::Data meshData;
		meshData.vertices.push_back({{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}, {{0x00, 0x00, 0xFF, 0xFF}}});
		meshData.vertices.push_back({{+0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}, {{0x00, 0xFF, 0x00, 0xFF}}});
		meshData.vertices.push_back({{+0.5f, +0.5f, 0.0f}, {1.0f, 1.0f}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
		meshData.vertices.push_back({{-0.5f, +0.5f, 0.0f}, {0.0f, 1.0f}, {{0xFF, 0x00, 0x00, 0xFF}}});

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

	enum class TileSurfaceFace : u32
	{
		Right = 0,
		Left = 1,
		Up = 2,
		Down = 3,
		Front = 4,
		Back = 5,
	};

	INTERNAL void addTileSurface(Mesh::Data* data, const Vector3& position, TileSurfaceFace face, const Vector2& tilePos)
	{
		const f32 tileWidth = 1.0f / 16.0f;
		const f32 tileHeight = 1.0f / 16.0f;

		usize index = data->vertices.size();

		// Right/Left
		if ((u32)face / 2 == 0)
		{
			data->vertices.push_back({{position.x + 0.0f, position.y + 0.0f, position.z + 1.0f}, {(tilePos.x + 1)*tileWidth, (tilePos.y + 0)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 0.0f, position.y + 0.0f, position.z + 0.0f}, {(tilePos.x + 0)*tileWidth, (tilePos.y + 0)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 0.0f, position.y + 1.0f, position.z + 0.0f}, {(tilePos.x + 0)*tileWidth, (tilePos.y + 1)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 0.0f, position.y + 1.0f, position.z + 1.0f}, {(tilePos.x + 1)*tileWidth, (tilePos.y + 1)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
		}
		// Up/Down
		else if ((u32)face / 2 == 1)
		{
			data->vertices.push_back({{position.x + 0.0f, position.y, position.z + 0.0f}, {(tilePos.x + 0)*tileWidth, (tilePos.y + 1)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 0.0f, position.y, position.z + 1.0f}, {(tilePos.x + 0)*tileWidth, (tilePos.y + 0)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 1.0f, position.y, position.z + 1.0f}, {(tilePos.x + 1)*tileWidth, (tilePos.y + 0)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 1.0f, position.y, position.z + 0.0f}, {(tilePos.x + 1)*tileWidth, (tilePos.y + 1)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
		}
		// Front/Back
		else if ((u32)face / 2 == 2)
		{
			data->vertices.push_back({{position.x + 0.0f, position.y + 0.0f, position.z + 0.0f}, {(tilePos.x + 1)*tileWidth, (tilePos.y + 0)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 1.0f, position.y + 0.0f, position.z + 0.0f}, {(tilePos.x + 0)*tileWidth, (tilePos.y + 0)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 1.0f, position.y + 1.0f, position.z + 0.0f}, {(tilePos.x + 0)*tileWidth, (tilePos.y + 1)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
			data->vertices.push_back({{position.x + 0.0f, position.y + 1.0f, position.z + 0.0f}, {(tilePos.x + 1)*tileWidth, (tilePos.y + 1)*tileHeight}, {{0xFF, 0xFF, 0xFF, 0xFF}}});
		}



		if ((u32)face % 2 == 0)
		{
			data->indices.push_back(index + 0);
			data->indices.push_back(index + 1);
			data->indices.push_back(index + 2);
			data->indices.push_back(index + 2);
			data->indices.push_back(index + 3);
			data->indices.push_back(index + 0);
		}
		else // (u32)face % 2 == 1
		{
			data->indices.push_back(index + 0);
			data->indices.push_back(index + 3);
			data->indices.push_back(index + 2);
			data->indices.push_back(index + 2);
			data->indices.push_back(index + 1);
			data->indices.push_back(index + 0);
		}
	}

	INTERNAL void addTileSurface(Mesh::Data* data, const Vector3& position, TileSurfaceFace face, const std::vector<Vector2>& randomTilePosSet)
	{
		usize length = randomTilePosSet.size();
		// TODO(bill): use better randomizer
		Vector2 tilePos = randomTilePosSet[rand() % length];
		addTileSurface(data, position, face, tilePos);
	}

	INTERNAL void generateWorld()
	{
		Mesh::Data floorMD;
		int mapWidth = 16;
		int mapDepth = 16;

		Vector2 lightWoodTile(0, 11);
		std::vector<Vector2> stoneTiles;
		for (int i = 1; i < 11; i++)
			stoneTiles.emplace_back(Vector2(i, 15));

		for (int i = 0; i < mapWidth; i++)
		{
			for (int j = 0; j < mapDepth; j++)
				addTileSurface(&floorMD, Vector3(i, 0, j), TileSurfaceFace::Up, lightWoodTile);
		}

		for (int k = 0; k < 3; k++)
		{
			for (int j = 0; j < mapDepth; j++)
				addTileSurface(&floorMD, Vector3(0, k, j), TileSurfaceFace::Right, stoneTiles);

			for (int j = 0; j < mapDepth; j++)
				addTileSurface(&floorMD, Vector3(mapWidth, k, j), TileSurfaceFace::Left, stoneTiles);

			for (int i = 0; i < mapWidth; i++)
				addTileSurface(&floorMD, Vector3(i, k, 0), TileSurfaceFace::Front, stoneTiles);

			for (int i = 0; i < mapWidth; i++)
				addTileSurface(&floorMD, Vector3(i, k, mapDepth), TileSurfaceFace::Back, stoneTiles);
		}


		ModelInstance floorMI;
		floorMI.asset = new ModelAsset();
		floorMI.asset->mesh = new Mesh(floorMD);
		floorMI.asset->material = &g_materials["terrain"];

		g_instances.push_back(floorMI);
	}

	INTERNAL void loadInstances()
	{
		Transform parent;

		ModelInstance a;
		a.asset = &g_sprite;
		a.transform.position = {4, 0.5, 4};
		a.transform.scale = {1, 1, 1};
		//a.transform.orientation = angleAxis(Degree(45), {0, 0, 1});
		g_instances.push_back(a);


		generateWorld();



		// Init Camera
		g_camera.transform.position = {4, 4, 10};

		g_camera.lookAt({4, 0, 0});
		//g_camera.projectionType = ProjectionType::Orthographic;
		//g_camera.orthoScale = 800;
		g_camera.projectionType = ProjectionType::Perspective;
		g_camera.fieldOfView = Degree(50.0f);
	}

	INTERNAL void update(f32 dt)
	{
		ModelInstance& player = g_instances[0];


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


#if 0 // Billboard
				Quaternion pRot = conjugate(quaternionLookAt(player.transform.position,
					g_camera.transform.position,
					{0, 1, 0}));


				player.transform.orientation = pRot;
#elif 0 // Billboard fixed y-axis
				Vector3 f = player.transform.position - g_camera.transform.position;
				f.y = 0;
				if (f.x == 0 && f.z == 0)
					player.transform.orientation = Quaternion();
				else
				{
					Radian a(-std::atan(f.z / f.x));
					a += Radian(Constants::TAU / 4);
					if (f.x < 0)
						a -= Radian(Constants::TAU / 2);

					player.transform.orientation = angleAxis(a, {0, 1, 0});
				}
#endif
			}
		}
		//g_camera.transform.position.x = player.transform.position.x;
		//g_camera.lookAt(player.transform.position);
		g_camera.viewportAspectRatio = getWindowSize().x / getWindowSize().y;



		//g_camera.lookAt({0, 0, 0});
	}

	INTERNAL void renderInstance(const ModelInstance& inst)
	{
		ModelAsset* asset = inst.asset;
		ShaderProgram* shaders = asset->material->shaders;

		shaders->setUniform("u_camera", g_camera.getMatrix());
		shaders->setUniform("u_transform", inst.transform);
		shaders->setUniform("u_tex", (u32)0);

		asset->mesh->draw();
	}

	INTERNAL void render()
	{
		glViewport(0, 0, windowWidth, windowHeight);

		glClearColor(0, 0, 0, 1);
		//glClearColor(0.5f, 0.69f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		const ShaderProgram* currentShaders = nullptr;
		const Texture* currentTexture = nullptr;

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
		//Input::setCursorMode(Input::CursorMode::Disabled);

		glEnable(GL_CULL_FACE);
		glCullFace(GL_BACK);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LEQUAL);


		loadShaders();
		loadMaterials();
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
