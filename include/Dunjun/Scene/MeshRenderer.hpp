#ifndef DUNJUN_SCENE_MESHRENDERER_HPP
#define DUNJUN_SCENE_MESHRENDERER_HPP

#include <Dunjun/Scene/NodeComponent.hpp>
#include <Dunjun/Scene/SceneRenderer.hpp>
#include <Dunjun/Graphics/Material.hpp>
#include <Dunjun/Graphics/Mesh.hpp>
#include <Dunjun/Graphics/ModelAsset.hpp>

namespace Dunjun
{
class MeshRenderer : public NodeComponent
{
public:
	explicit MeshRenderer(const Mesh* mesh, Material* material)
	: mesh{mesh}
	, material{material}
	{
	}

	explicit MeshRenderer(const ModelAsset& asset)
	: mesh{asset.mesh}
	, material{asset.material}
	{
	}

	virtual void draw(SceneRenderer& renderer, Transform t) const override
	{
		if (!material || !mesh)
			return;

		renderer.addModelInstance(*this, t);
	}

	const Mesh* mesh;
	Material* material;
};
} // namespace Dunjun

#endif
