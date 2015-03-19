#ifndef DUNJUN_RENDERER_HPP
#define DUNJUN_RENDERER_HPP

#include <Dunjun/Material.hpp>
#include <Dunjun/Camera.hpp>
#include <Dunjun/Drawable.hpp>
#include <Dunjun/Mesh.hpp>

namespace Dunjun
{
class Drawable;

class Renderer : private NonCopyable
{
public:
	Renderer();

	virtual ~Renderer() {}

	void reset();

	void draw(const Drawable& node, Transform t = Transform());
	void draw(const Mesh* mesh) const;

	void setMaterial(const Material* material);

	void setCamera(const Camera& camera);

	void setUniforms(const Transform& t);

private:
	void setShaders(const ShaderProgram* shaders);
	void setTexture(const Texture* texture);

	const Material* m_currentMaterial = nullptr;
	const ShaderProgram* m_currentShaders = nullptr;
	const Texture* m_currentTexture = nullptr;
	const Camera* m_currentCamera = nullptr;
};
} // namespace Dunjun

#endif
