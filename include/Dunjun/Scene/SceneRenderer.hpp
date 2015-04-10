#ifndef DUNJUN_SCENE_SCENERENDERER_HPP
#define DUNJUN_SCENE_SCENERENDERER_HPP

#include <Dunjun/Material.hpp>
#include <Dunjun/Camera.hpp>
#include <Dunjun/ModelAsset.hpp>
#include <Dunjun/Scene/Lighting.hpp>
#include <Dunjun/RenderTexture.hpp>
#include <Dunjun/GBuffer.hpp>

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
		const MeshRenderer* meshRenderer;
		Transform transform;
	};

	SceneRenderer();

	virtual ~SceneRenderer()
	{
		delete lightingTexture;
		delete m_gBuffer;
	}

	void reset(); // Reset all pointers
	void clearAll(); // clear all containers

	void addSceneGraph(const SceneNode& node, Transform t = Transform());
	void draw(const Mesh* mesh) const;

	void addModelInstance(const MeshRenderer& meshRenderer, Transform t);
	void addPointLight(const PointLight* light);

	void renderAll();

	void deferredGeometryPass();
	void deferredLightPass();

	void setCamera(const Camera& camera);

	inline void createGBuffer(u32 width, u32 height)
	{
		if (m_gBuffer == nullptr)
			m_gBuffer = new GBuffer();

		m_gBuffer->create(width, height);
	}

	inline GBuffer* getGBuffer()
	{
		if (m_gBuffer == nullptr)
		{
			auto fbSize = Window::getFramebufferSize();
			createGBuffer(fbSize.x, fbSize.y);
		}

		return m_gBuffer;
	}

	const Camera* camera = nullptr;

	ShaderProgram* geometryPassShaders = nullptr;
	const ShaderProgram* pointLightShaders = nullptr;

	const Mesh* quad;

	RenderTexture* lightingTexture;

	std::deque<ModelInstance> modelInstances;
	std::deque<const PointLight*> pointsLights;

private:
	bool setShaders(const ShaderProgram* shaders);
	bool setTexture(const Texture* texture, GLuint position);

	const Material* m_currentMaterial = nullptr;
	const ShaderProgram* m_currentShaders = nullptr;
	const Texture* m_currentTexture = nullptr;

	GBuffer* m_gBuffer = nullptr;


};
} // namespace Dunjun

#endif
