#ifndef DUNJUN_RENDERER_HPP
#define DUNJUN_RENDERER_HPP

#include <Dunjun/ShaderProgram.hpp>
#include <Dunjun/Texture.hpp>
#include <Dunjun/Camera.hpp>

namespace Dunjun
{
class SceneNode;

class Renderer : private NonCopyable
{
public:
	Renderer();

	virtual ~Renderer() {}

	void reset();

	void draw(const SceneNode& node, Transform t = Transform());

	void setShaders(ShaderProgram* shaders);
	void setTexture(const Texture* texture);
	void setCamera(const Camera& camera);

	void setUniforms(const Transform& t);

private:
	ShaderProgram* m_currentShaders = nullptr;
	const Texture* m_currentTexture = nullptr;
	const Camera* m_currentCamera = nullptr;
};
} // namespace Dunjun

#endif
