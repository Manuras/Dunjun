#include <Dunjun/Config.hpp>
#include <Dunjun/Game.hpp>

#include <Dunjun/System.hpp>
#include <Dunjun/Window.hpp>
#include <Dunjun/ResourceHolders.hpp>
#include <Dunjun/World.hpp>

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
GLOBAL const u32 FrameLimit{288};

GLOBAL bool g_running{true};
} // namespace (anonymous)

GLOBAL Window g_window;

GLOBAL ModelAsset g_sprite;

GLOBAL World g_world;

namespace Game
{
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
	g_shaderHolder.insertFromFile("deferredSpotLight",
	                              "deferredLightPass.vert.glsl",
	                              "deferredSpotLight.frag.glsl");

	g_shaderHolder.insertFromFile("deferredOut",
	                              "deferredLightPass.vert.glsl",
	                              "deferredOut.frag.glsl");
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

INTERNAL void update(Time dt)
{
	g_world.update(dt);

	if (!g_window.isOpen() || Input::isKeyPressed(Input::Key::Escape))
		g_running = false;

	if (Input::isKeyPressed(Input::Key::F11))
	{
		// TODO(bill): Toggle fullscreen

		// Initial OpenGL settings
		glInit();
	}
}

INTERNAL void handleEvents()
{
	Event event;
	while (g_window.pollEvent(event))
	{
		switch (event.type)
		{
		case Event::Closed:
		{

			g_window.close();
			std::exit(EXIT_SUCCESS); // TODO(bill): Remove this exit
			break;
		}

		case Event::Resized:
		{
			glViewport(0, 0, event.size.width, event.size.height);
			break;
		}

		case Event::ControllerConnected:
		{
			printf("Controller %d added\n", event.controller.index);
			break;
		}

		case Event::ControllerDisconnected:
		{
			printf("Controller %d removed\n", event.controller.index);
			break;
		}

		default:
		{
			break;
		}
		}

		g_world.handleEvent(event);
	}
}


INTERNAL void render()
{
	g_world.render();
}

void init()
{
	u32 sdlFlags{
		SDL_INIT_VIDEO          |
		SDL_INIT_EVENTS         |
		SDL_INIT_JOYSTICK       |
		SDL_INIT_GAMECONTROLLER |
		SDL_INIT_HAPTIC         |
		0
	};
	if (SDL_Init(sdlFlags) != 0)
	{
		std::cerr << "SDL Failed to initialize. Error: ";
		std::cerr << SDL_GetError();
		std::cerr << std::endl;
		std::exit(EXIT_FAILURE);
	}

	g_window.create({854, 480}, "Dunjun");
	g_window.setFramerateLimit(FrameLimit);

	glewInit();

	// Initial OpenGL settings
	glInit();

	Input::setup();
	Input::setCursorPosition(g_window, {0, 0});

	loadShaders();
	loadMaterials();
	loadSpriteAsset();

	g_world.init(Context{
		g_window,
		g_textureHolder,
		g_shaderHolder,
		g_meshHolder,
		g_materialHolder
	});
}

void run()
{
	TickCounter tc;

	Time accumulator;
	Time prevTime{Time::now()};

	usize frames{0};

	while (g_running)
	{
		Time currentTime{Time::now()};
		Time dt{currentTime - prevTime};
		prevTime = currentTime;
		accumulator += dt;

		if (accumulator > milliseconds(1200)) // remove loop of death
			accumulator = milliseconds(1200);

		handleEvents();

		while (accumulator >= TimeStep)
		{
			accumulator -= TimeStep;

			handleEvents();
			update(TimeStep);
		}

		// Set Window Title
		if (tc.update(milliseconds(500)))
		{
			g_window.setTitle(
				stringFormat("Dunjun - %.3f ms - %d fps",
				             1000.0f / tc.getTickRate(),
				             (u32)tc.getTickRate()));
		}

		render();

		g_window.display();
	}
}

void cleanup()
{
	Input::cleanup();
	g_window.close();
	SDL_Quit();

	std::exit(EXIT_SUCCESS);
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
