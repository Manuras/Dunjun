#ifndef DUNJUN_SCENE_SCENERENDERER_HPP
#define DUNJUN_SCENE_SCENERENDERER_HPP

#include <Dunjun/Graphics/Material.hpp>
#include <Dunjun/Graphics/Camera.hpp>
#include <Dunjun/Graphics/ModelAsset.hpp>
#include <Dunjun/Scene/Lighting.hpp>
#include <Dunjun/Graphics/RenderTexture.hpp>
#include <Dunjun/Graphics/GBuffer.hpp>

#include <deque>

#include <Dunjun/Window.hpp>

namespace Dunjun
{
class SceneNode;
class MeshRenderer;

class SceneRenderer : private NonCopyable
{
public:
	struct ModelInstance
	{
		ModelInstance() = default;
		ModelInstance(const MeshRenderer& meshRenderer, const Transform& transform)
		: meshRenderer{&meshRenderer}
		, transform{transform}
		{
		}


		const MeshRenderer* meshRenderer;
		Transform transform;
	};

	SceneRenderer();

	virtual ~SceneRenderer()
	{
	}

	void reset(); // Reset all pointers
	void clearAll(); // clear all containers

	void addSceneGraph(const SceneNode& node, Transform t = Transform{});
	void draw(const Mesh* mesh) const;

	void addModelInstance(const MeshRenderer& meshRenderer, Transform t);
	void addPointLight(const PointLight* light);
	void addSpotLight(const SpotLight* light);
	void addDirectionalLight(const DirectionalLight* light);

	void geometryPass();
	void lightPass();
	void outPass();

	void setCamera(const Camera& camera);

	const Camera* camera{nullptr};

	GBuffer gBuffer;
	RenderTexture lightingTexture;
	RenderTexture outTexture;

private:
	void renderAmbientLight();
	void renderDirectionLights();
	void renderPointLights();
	void renderSpotLights();

	bool setShaders(const ShaderProgram* shaders);
	bool setTexture(const Texture* texture, u32 position);

	const Material* m_currentMaterial{nullptr};
	const ShaderProgram* m_currentShaders{nullptr};
	const Texture* m_currentTexture{nullptr};

	std::deque<const DirectionalLight*> m_directionalLights;
	std::deque<const PointLight*> m_pointsLights;
	std::deque<const SpotLight*> m_spotLights;

	std::deque<ModelInstance> m_modelInstances;
};
} // namespace Dunjun

#endif
