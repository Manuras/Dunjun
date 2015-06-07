#include <Dunjun/Scene/SceneRenderer.hpp>

#include <Dunjun/Scene/SceneNode.hpp>
#include <Dunjun/Scene/MeshRenderer.hpp>
#include <Dunjun/World.hpp>

#include <string>

#include <algorithm>
#include <iterator>

namespace Dunjun
{

SceneRenderer::SceneRenderer(World& world)
: m_world{world}
// Defaults
, m_fbWidth{512}
, m_fbHeight{512}
{
}

SceneRenderer& SceneRenderer::reset()
{
	if (m_currentShaders)
		m_currentShaders->stopUsing();
	m_currentShaders = nullptr;

	m_currentTexture = nullptr;
	Texture::bind(nullptr, 0);

	m_currentMaterial = nullptr;

	return *this;
}

SceneRenderer& SceneRenderer::clearAll()
{
	m_modelInstances.clear();

	return *this;
}

SceneRenderer& SceneRenderer::addSceneGraph(const SceneNode& node, Transform t)
{
	node.draw(*this, t);

	return *this;
}

void SceneRenderer::draw(const Mesh* mesh) const
{
	if (mesh)
		mesh->draw();
}

void SceneRenderer::addModelInstance(const MeshRenderer& meshRenderer,
                                     Transform t)
{
	if (meshRenderer.getParent()->visible) // Just in case
		m_modelInstances.emplace_back(meshRenderer, t);
}

SceneRenderer& SceneRenderer::setFramebufferSize(u32 width, u32 height)
{
	m_fbWidth = width;
	m_fbHeight = height;

	return *this;
}

SceneRenderer& SceneRenderer::setCamera(const Camera& camera)
{
	m_camera = &camera;

	return *this;
}

void SceneRenderer::render()
{
	reset().clearAll();
	
	addSceneGraph(m_world.m_sceneGraph).setCamera(*m_world.m_currentCamera);

	m_gBuffer.create(m_fbWidth, m_fbHeight);

	geometryPass().lightPass().outPass();
}

SceneRenderer& SceneRenderer::geometryPass()
{
	// TODO(bill): Sort by mesh? - Instancing?
	std::sort(std::begin(m_modelInstances),
			  std::end(m_modelInstances),
	          [](const ModelInstance& a, const ModelInstance& b) -> bool
	          {
		          const auto* A = a.meshRenderer->material;
		          const auto* B = b.meshRenderer->material;

		          if (A != B && A && B)
		          {
			          if (A->shaders == B->shaders)
				          return A->diffuseMap < B->diffuseMap;
			          return A->shaders < B->shaders;
		          }
		          return false;
		      });

	auto& shaders = g_shaderHolder.get("deferredGeometryPass");

	GBuffer::bind(&m_gBuffer);
	{
		glViewport(0, 0, m_gBuffer.getWidth(), m_gBuffer.getHeight());
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaders.use();

		shaders.setUniform("u_camera", m_camera->getMatrix());
		shaders.setUniform("u_cameraPosition", m_camera->transform.position);
		for (const auto& inst : m_modelInstances)
		{
			if (inst.meshRenderer->material == nullptr)
				continue;

			{
				shaders.setUniform("u_material.diffuseMap", (int)0);
				shaders.setUniform("u_material.diffuseColor",
				                   inst.meshRenderer->material->diffuseColor);
				shaders.setUniform("u_material.specularColor",
				                   inst.meshRenderer->material->specularColor);
				shaders.setUniform(
				    "u_material.specularExponent",
				    inst.meshRenderer->material->specularExponent);
			}
			setTexture(inst.meshRenderer->material->diffuseMap, 0);

			shaders.setUniform("u_transform", inst.transform);

			draw(inst.meshRenderer->mesh);
		}

		glFlush();
	}
	GBuffer::bind(nullptr);

	return *this;
}

SceneRenderer& SceneRenderer::lightPass()
{
	m_lightingTexture.create(m_gBuffer.getWidth(), m_gBuffer.getHeight(), RenderTexture::Lighting);

	Texture::bind(&m_gBuffer.getTexture(GBuffer::Diffuse),  0);
	Texture::bind(&m_gBuffer.getTexture(GBuffer::Specular), 1);
	Texture::bind(&m_gBuffer.getTexture(GBuffer::Normal),   2);
	Texture::bind(&m_gBuffer.getTexture(GBuffer::Depth),    3);

	RenderTexture::bind(&m_lightingTexture);
	{
		glClearColor(0, 0, 0, 0);
		glViewport(0, 0, m_lightingTexture.getWidth(), m_lightingTexture.getHeight());
		glClear(GL_COLOR_BUFFER_BIT);

		glDepthMask(false);
		glEnable(GL_BLEND);
		glBlendFunc(GL_ONE, GL_ONE);

		// Ambient Light
		{
			auto& shaders = g_shaderHolder.get("deferredAmbientLight");

			shaders.use();
			
			Vector3 intensities{};
			intensities.r = m_ambientColor.r * m_ambientIntensity;
			intensities.g = m_ambientColor.g * m_ambientIntensity;
			intensities.b = m_ambientColor.b * m_ambientIntensity;
			intensities /= 255.0f;

			shaders.setUniform("u_light.intensities", intensities);

			draw(&g_meshHolder.get("quad"));

			shaders.stopUsing();
		}
		// Directional Lights
		{
			auto& shaders = g_shaderHolder.get("deferredDirectionalLight");

			shaders.use();
			shaders.setUniform("u_specular", 1);
			shaders.setUniform("u_normal", 2);

			for (const auto& light : m_world.m_directionalLights)
			{
				Vector3 lightIntensities;

				lightIntensities.r = light.color.r / 255.0f;
				lightIntensities.g = light.color.g / 255.0f;
				lightIntensities.b = light.color.b / 255.0f;
				lightIntensities *= light.intensity;

				shaders.setUniform("u_light.base.intensities", lightIntensities);
				shaders.setUniform("u_light.direction", normalize(light.direction));

				draw(&g_meshHolder.get("quad"));
			}
			shaders.stopUsing();
		}
		// Point Lights
		{
			auto& shaders = g_shaderHolder.get("deferredPointLight");

			shaders.use();
			shaders.setUniform("u_diffuse", 0);
			shaders.setUniform("u_specular", 1);
			shaders.setUniform("u_normal", 2);
			shaders.setUniform("u_depth", 3);

			shaders.setUniform("u_cameraInverse", inverse(m_camera->getMatrix()));

			for (const PointLight& light : m_world.m_pointLights)
			{
				light.calculateRange();

				Vector3 lightIntensities;

				lightIntensities.r = light.color.r / 255.0f;
				lightIntensities.g = light.color.g / 255.0f;
				lightIntensities.b = light.color.b / 255.0f;
				lightIntensities *= light.intensity;

				shaders.setUniform("u_light.base.intensities", lightIntensities);
				shaders.setUniform("u_light.position", light.position);

				shaders.setUniform("u_light.attenuation.constant",
								   light.attenuation.constant);
				shaders.setUniform("u_light.attenuation.linear",
								   light.attenuation.linear);
				shaders.setUniform("u_light.attenuation.quadratic",
								   light.attenuation.quadratic);

				shaders.setUniform("u_light.range", light.range);

				draw(&g_meshHolder.get("quad"));
			}

			shaders.stopUsing();
		}
		// Spot Lights
		{
			auto& shaders = g_shaderHolder.get("deferredSpotLight");

			shaders.use();
			shaders.setUniform("u_diffuse", 0);
			shaders.setUniform("u_specular", 1);
			shaders.setUniform("u_normal", 2);
			shaders.setUniform("u_depth", 3);

			shaders.setUniform("u_cameraInverse", inverse(m_camera->getMatrix()));

			for (const SpotLight& light : m_world.m_spotLights)
			{
				light.calculateRange();

				Vector3 lightIntensities;

				lightIntensities.r = light.color.r / 255.0f;
				lightIntensities.g = light.color.g / 255.0f;
				lightIntensities.b = light.color.b / 255.0f;
				lightIntensities *= light.intensity;

				shaders.setUniform("u_light.point.base.intensities", lightIntensities);
				shaders.setUniform("u_light.point.position", light.position);

				shaders.setUniform("u_light.point.attenuation.constant",
								   light.attenuation.constant);
				shaders.setUniform("u_light.point.attenuation.linear",
								   light.attenuation.linear);
				shaders.setUniform("u_light.point.attenuation.quadratic",
								   light.attenuation.quadratic);

				shaders.setUniform("u_light.point.range", light.range);

				shaders.setUniform("u_light.direction", light.direction);
				shaders.setUniform("u_light.coneAngle", static_cast<f32>(light.coneAngle));

				draw(&g_meshHolder.get("quad"));
			}

			shaders.stopUsing();
		}

		glDisable(GL_BLEND);
		glDepthMask(true);
	}
	RenderTexture::bind(nullptr);

	return *this;
}

SceneRenderer& SceneRenderer::outPass()
{
	m_outTexture.create(m_gBuffer.getWidth(), m_gBuffer.getHeight(), RenderTexture::Color);

	Texture::bind(&m_gBuffer.getTexture(GBuffer::Diffuse), 0);
	Texture::bind(&m_lightingTexture.colorTexture, 1);

	RenderTexture::bind(&m_outTexture);
	{
		glClearColor(1, 1, 1, 1);
		glViewport(0, 0, m_outTexture.getWidth(), m_outTexture.getHeight());
		glClear(GL_COLOR_BUFFER_BIT);

		auto& shaders = g_shaderHolder.get("deferredOut");

		shaders.use();
		shaders.setUniform("u_diffuse", 0);
		shaders.setUniform("u_lighting", 1);

		draw(&g_meshHolder.get("quad"));

		shaders.stopUsing();
	}
	RenderTexture::bind(nullptr);

	return *this;
}

bool SceneRenderer::setShaders(const ShaderProgram* shaders)
{
	if (shaders != m_currentShaders)
	{
		if (m_currentShaders)
			m_currentShaders->stopUsing();

		m_currentShaders = shaders;
		m_currentShaders->use();

		return true;
	}

	return false;
}

bool SceneRenderer::setTexture(const Texture* texture, u32 position)
{
	if (texture != m_currentTexture)
	{
		m_currentTexture = texture;

		Texture::bind(m_currentTexture, position);

		return true;
	}

	return false;
}
} // namespace Dunjun
