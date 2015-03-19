#ifndef DUNJUN_SCENE_MESHRENDERER_HPP
#define DUNJUN_SCENE_MESHRENDERER_HPP

#include <Dunjun/Scene/NodeComponent.hpp>
#include <Dunjun/Renderer.hpp>
#include <Dunjun/Material.hpp>
#include <Dunjun/Mesh.hpp>
#include <Dunjun/ModelAsset.hpp>

namespace Dunjun
{
class MeshRenderer : public NodeComponent
{
public:
	explicit MeshRenderer(const Mesh* mesh, const Material* material)
	: mesh(mesh)
	, material(material)
	{
	}

	explicit MeshRenderer(const ModelAsset& asset)
	: mesh(asset.mesh)
	, material(asset.material)
	{
	}

	virtual void draw(Renderer& renderer, Transform t) const
	{
		if (!material || !mesh)
			return;

		renderer.setMaterial(material);
		renderer.setUniforms(t);

		renderer.draw(mesh);
	}

	const Mesh* mesh;
	const Material* material;
};
} // namespace Dunjun

#endif
