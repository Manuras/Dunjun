#include <Dunjun/World.hpp>

#include <Dunjun/Math/Random.hpp>

namespace Dunjun
{
World::World(Context context)
: context{context}
{

}

World::~World()
{

}

void World::init()
{
	m_sceneGraph.init();
	{
		// auto player = make_unique<SceneNode>();

		// player->name = "player";
		// player->transform.position = {2, 0.5, 2};
		// player->transform.orientation = angleAxis(Degree{45}, {0, 1, 0});
		// player->addComponent<MeshRenderer>(m_sprite);
		// player->addComponent<FaceCamera>(m_mainCamera);

		// m_player = player.get();

		// m_rootNode.attachChild(std::move(player));
	}

	{
		auto level = make_unique<Level>();

		level->material = &context.materialHolder.get("terrain");
		level->generate();

		m_level = level.get();

		m_sceneGraph.attachChild(std::move(level));
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

		m_pointLights.emplace_back(light);
	}

	{
		DirectionalLight light;
		light.color = Color{255, 255, 250};
		light.direction = Vector3{-1, -1, 0.5};
		light.intensity = 0.1f;

		m_directionalLights.emplace_back(light);
	}

	{
		SpotLight light;
		light.color = Color{255, 255, 250};
		light.direction = {0, -1, 0};
		light.position = {4, 1.5f, 4};
		light.intensity = 2.0f;
		light.coneAngle = Degree{50};

		m_spotLights.emplace_back(light);
	}

	{
		// Init Camera
		m_playerCamera.transform.position = {5, 2, 5};
		m_playerCamera.transform.orientation =
		    angleAxis(Degree{45}, {0, 1, 0}) * angleAxis(Degree{-30}, {1, 0, 0});

		m_playerCamera.fieldOfView = Degree{50.0f};
		m_playerCamera.orthoScale = 8;

		m_mainCamera = m_playerCamera;

		m_playerCamera.projectionType = ProjectionType::Orthographic;

	}

	m_currentCamera = &m_mainCamera;
}



void World::update(Time dt)
{
	m_sceneGraph.update(dt);
}

void World::handleEvent(const Event& event)
{
	m_sceneGraph.handleEvent(event);
}

void World::draw()
{
	// TODO(bill):

	Window::Dimensions fbSize{context.window.getSize()};

	m_renderer.reset();
	m_renderer.clearAll();
	m_renderer.addSceneGraph(m_sceneGraph);

	for (const auto& light : m_pointLights)
		m_renderer.addPointLight(&light);
	for (const auto& light : m_directionalLights)
		m_renderer.addDirectionalLight(&light);
	for (const auto& light : m_spotLights)
		m_renderer.addSpotLight(&light);

	m_renderer.camera = m_currentCamera;

	m_renderer.gBuffer.create(fbSize.width, fbSize.height);

	m_renderer.geometryPass();
	m_renderer.lightPass();
	m_renderer.outPass();

	// context.materialHolder.get("cat").diffuseMap =
	//     &m_renderer.lightingTexture.colorTexture;

	glViewport(0, 0, fbSize.width, fbSize.height);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{
		ShaderProgram& shaders = context.shaderHolder.get("texPass");
		shaders.use();

		shaders.setUniform("u_scale", Vector3{1.0f});
		shaders.setUniform("u_tex", 0);
		Texture::bind(&m_renderer.outTexture.colorTexture, 0);
		// Texture::bind(&m_renderer.lightingTexture.colorTexture, 0);


		m_renderer.draw(&context.meshHolder.get("quad"));

		shaders.stopUsing();
	}
}


SceneNode& World::getSceneGraph()
{
	return m_sceneGraph;
}

const SceneNode& World::getSceneGraph() const
{
	return m_sceneGraph;
}


Camera& World::getCurrentCamera()
{
	return *m_currentCamera;
}

const Camera& World::getCurrentCamera() const
{
	return *m_currentCamera;
}


SceneNode* World::getPlayer()
{
	return m_player;
}

const SceneNode* World::getPlayer() const
{
	return m_player;

}


Level* World::getLevel()
{
	return m_level;
}

const Level* World::getLevel() const
{
	return m_level;

}

} // namespace Dunjun
