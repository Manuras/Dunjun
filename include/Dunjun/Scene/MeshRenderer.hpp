#ifndef DUNJUN_SCENE_MESHRENDERER_HPP
#define DUNJUN_SCENE_MESHRENDERER_HPP

#include <Dunjun/Scene/NodeComponent.hpp>
#include <Dunjun/Material.hpp>
#include <Dunjun/Mesh.hpp>

namespace Dunjun
{
class MeshRenderer : public NodeComponent
{
public:

	explicit MeshRenderer(const Mesh& mesh, const Material& material);

	virtual void draw(Transform t);

	const Mesh* m_mesh;
	const Material* m_material;
};
} // namespace Dunjun

#endif
