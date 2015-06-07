#ifndef DUNJUN_SCENE_SCENERENDERER_HPP
#define DUNJUN_SCENE_SCENERENDERER_HPP

#include <Dunjun/Graphics/Material.hpp>
#include <Dunjun/Graphics/Camera.hpp>
#include <Dunjun/Graphics/ModelAsset.hpp>
#include <Dunjun/Scene/Lighting.hpp>
#include <Dunjun/Graphics/RenderTexture.hpp>
#include <Dunjun/Graphics/GBuffer.hpp>
#include <Dunjun/Window.hpp>

#include <deque>

namespace Dunjun
{
class SceneNode;
class MeshRenderer;
class World;

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

	SceneRenderer(World& world);

	virtual ~SceneRenderer()
	{
	}

	SceneRenderer& reset(); // Reset all pointers
	SceneRenderer& clearAll(); // clear all containers

	SceneRenderer& addSceneGraph(const SceneNode& node, Transform t = Transform{});
	void draw(const Mesh* mesh) const;

	void addModelInstance(const MeshRenderer& meshRenderer, Transform t);

	void render();

	SceneRenderer& geometryPass();
	SceneRenderer& lightPass();
	SceneRenderer& outPass();

	SceneRenderer& setFramebufferSize(u32 width, u32 height);
	SceneRenderer& setCamera(const Camera& camera);
	SceneRenderer& setAmbientLight(const Color& color, f32 intensity);

	const GBuffer& getGBuffer() const { return m_gBuffer; }
	const Texture& getFinalTexture() const { return m_outTexture.colorTexture; }	

private:
	bool setShaders(const ShaderProgram* shaders);
	bool setTexture(const Texture* texture, u32 position);

	World& m_world;

	u32 m_fbWidth{512};
	u32 m_fbHeight{512};

	GBuffer m_gBuffer;

	RenderTexture m_lightingTexture;
	RenderTexture m_outTexture;

	Color m_ambientColor{222, 227, 234};
	f32   m_ambientIntensity{0.02f};

	const Camera* m_camera{nullptr};
	const Material* m_currentMaterial{nullptr};
	const ShaderProgram* m_currentShaders{nullptr};
	const Texture* m_currentTexture{nullptr};

	std::deque<ModelInstance> m_modelInstances;
};
} // namespace Dunjun

#endif
