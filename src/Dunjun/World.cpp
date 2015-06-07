#include <Dunjun/World.hpp>

#include <Dunjun/Math/Random.hpp>

#include <Dunjun/Window/Input.hpp>

#include <Dunjun/Scene/MeshRenderer.hpp>
#include <Dunjun/Scene/FaceCamera.hpp>

namespace Dunjun
{
World::World() {}

World::~World() {}

void World::init(Context context)
{
	m_context = context;

	{
		auto player = make_unique<SceneNode>();

		player->name = "player";
		player->transform.position = {2, 0.5, 2};
		player->transform.orientation = angleAxis(Degree{45}, {0, 1, 0});
		player->addComponent<MeshRenderer>(
		    &m_context.meshHolder->get("sprite"),
		    &m_context.materialHolder->get("cat"));

		// player->addComponent<FaceCamera>(m_mainCamera);

		m_player = player.get();

		m_sceneGraph.attachChild(std::move(player));
	}

	{
		auto level = make_unique<Level>();

		level->material = &m_context.materialHolder->get("terrain");
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
		    angleAxis(Degree{45}, {0, 1, 0}) *
		    angleAxis(Degree{-30}, {1, 0, 0});

		m_playerCamera.fieldOfView = Degree{50.0f};
		m_playerCamera.orthoScale = 8;

		m_mainCamera = m_playerCamera;

		m_playerCamera.projectionType = ProjectionType::Orthographic;
	}

	m_currentCamera = &m_mainCamera;

	m_sceneGraph.init();
}

void World::update(Time dt)
{
	m_sceneGraph.update(dt);

	f32 camVel{10.0f};
	{
		if (Input::isControllerPresent(0))
		{
			f32 ltsX{Input::getControllerAxis(0, Input::ControllerAxis::LeftX)};
			f32 ltsY{Input::getControllerAxis(0, Input::ControllerAxis::LeftY)};

			f32 rtsX{
			    Input::getControllerAxis(0, Input::ControllerAxis::RightX)};
			f32 rtsY{
			    Input::getControllerAxis(0, Input::ControllerAxis::RightY)};

			const f32 lookSensitivity{2.0f};
			const f32 deadZone{0.21f};

			Vector2 rts{rtsX, rtsY};
			if (Math::abs(rts.x) < deadZone)
				rts.x = 0;
			if (Math::abs(rts.y) < deadZone)
				rts.y = 0;

			m_mainCamera.offsetOrientation(
			    lookSensitivity * Radian{-rts.x * dt.asSeconds()},
			    lookSensitivity * Radian{-rts.y * dt.asSeconds()});

			Vector2 lts{ltsX, ltsY};

			if (Math::abs(lts.x) < deadZone)
				lts.x = 0;
			if (Math::abs(lts.y) < deadZone)
				lts.y = 0;

			if (length(lts) > 1.0f)
				lts = normalize(lts);
			Vector3 velDir{0, 0, 0};

			Vector3 forward{m_mainCamera.forward()};
			forward.y = 0;
			forward = normalize(forward);
			velDir += lts.x * m_mainCamera.right();
			velDir += lts.y * forward;

			if (Input::isControllerButtonPressed(
			        0, Input::ControllerButton::RightShoulder))
				velDir.y += 1;
			if (Input::isControllerButtonPressed(
			        0, Input::ControllerButton::LeftShoulder))
				velDir.y -= 1;

			if (Input::isControllerButtonPressed(
			        0, Input::ControllerButton::DpadUp))
			{
				Vector3 f{m_mainCamera.forward()};
				f.y = 0;
				f = normalize(f);
				velDir += f;
			}
			if (Input::isControllerButtonPressed(
			        0, Input::ControllerButton::DpadDown))
			{
				Vector3 b{m_mainCamera.backward()};
				b.y = 0;
				b = normalize(b);
				velDir += b;
			}

			if (Input::isControllerButtonPressed(
			        0, Input::ControllerButton::DpadLeft))
			{
				Vector3 l{m_mainCamera.left()};
				l.y = 0;
				l = normalize(l);
				velDir += l;
			}
			if (Input::isControllerButtonPressed(
			        0, Input::ControllerButton::DpadRight))
			{
				Vector3 r{m_mainCamera.right()};
				r.y = 0;
				r = normalize(r);
				velDir += r;
			}

			if (length(velDir) > 1.0f)
				velDir = normalize(velDir);

			m_mainCamera.transform.position += camVel * velDir * dt.asSeconds();

			// Vibrate
			if (Input::isControllerButtonPressed(0, Input::ControllerButton::A))
			{
				Input::setControllerVibration(0, 0.5f, 0.5f);
			}
			else
			{
				Input::setControllerVibration(0, 0.0f, 0.0f);
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
			m_player->transform.position += playerVel * velDir * dt.asSeconds();

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

	m_playerCamera.transform.position.x =
	    Math::lerp(m_playerCamera.transform.position.x,
	               m_player->transform.position.x,
	               10.0f * dt.asSeconds());
	m_playerCamera.transform.position.z =
	    Math::lerp(m_playerCamera.transform.position.z,
	               m_player->transform.position.z,
	               10.0f * dt.asSeconds());

	// g_camera.transform.position.x = player.transform.position.x;
	f32 aspectRatio{m_context.window->getSize().aspectRatio()};
	if (aspectRatio && m_context.window->getSize().height > 0)
	{
		m_playerCamera.viewportAspectRatio = aspectRatio;
		m_mainCamera.viewportAspectRatio = aspectRatio;
	}

	if (Input::isKeyPressed(Input::Key::Num1))
		m_currentCamera = &m_playerCamera;
	else if (Input::isKeyPressed(Input::Key::Num2))
	{
		m_mainCamera.transform = m_playerCamera.transform;
		m_currentCamera = &m_mainCamera;
	}

#if 1
	// TODO(bill): Make bounding boxes for SceneNodes and implement this
	// in SceneRenderer
	for (auto& room : m_level->rooms)
	{
		Vector3 roomPos{room->transform.position};
		roomPos.x += room->size.x / 2;
		roomPos.z += room->size.y / 2;
		const Vector3 playerPos{m_mainCamera.transform.position};

		const Vector3 dp{roomPos - playerPos};

		const f32 dist{length(dp)};

		// Distance Culling
		if (dist < m_mainCamera.farPlane)
		{
			const Vector3 f{m_mainCamera.forward()};

			f32 cosTheta{dot(f, normalize(dp))};

			Radian theta{Math::acos(cosTheta)};

			// Cone/(bad) Frustum Culling
			if (Math::abs(theta) <= 2.0f * m_mainCamera.fieldOfView ||
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

void World::handleEvent(const Event& event)
{
	// m_sceneGraph.handleEvent(event);
}

void World::render()
{
	// TODO(bill):

	Window::Dimensions fbSize{m_context.window->getSize()};

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

	// m_context.materialHolder->get("cat").diffuseMap =
	//     &m_renderer.lightingTexture.colorTexture;

	glViewport(0, 0, fbSize.width, fbSize.height);
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	{
		ShaderProgram& shaders = m_context.shaderHolder->get("texPass");
		shaders.use();

		shaders.setUniform("u_scale", Vector3{1.0f});
		shaders.setUniform("u_tex", 0);
		Texture::bind(&m_renderer.outTexture.colorTexture, 0);
		// Texture::bind(&m_renderer.lightingTexture.colorTexture, 0);

		m_renderer.draw(&m_context.meshHolder->get("quad"));

		shaders.stopUsing();
	}
}

SceneNode& World::getSceneGraph() { return m_sceneGraph; }

const SceneNode& World::getSceneGraph() const { return m_sceneGraph; }

Camera& World::getCurrentCamera() { return *m_currentCamera; }

const Camera& World::getCurrentCamera() const { return *m_currentCamera; }

SceneNode* World::getPlayer() { return m_player; }

const SceneNode* World::getPlayer() const { return m_player; }

Level* World::getLevel() { return m_level; }

const Level* World::getLevel() const { return m_level; }

} // namespace Dunjun
