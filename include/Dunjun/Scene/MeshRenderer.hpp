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
	explicit MeshRenderer(const Mesh& mesh, const Material& material)
	: mesh(&mesh)
	, material(&material)
	{
	}

	explicit MeshRenderer(const ModelAsset& asset)
	: mesh(asset.mesh)
	, material(asset.material)
	{
	}

	virtual void draw(Renderer& renderer, Transform t)
	{
		ShaderProgram* shaders = material->shaders;
		const Texture* tex = material->texture;

		if (!shaders || !tex)
			return;

		renderer.setShaders(shaders);
		renderer.setTexture(tex);
		renderer.setUniforms(t);

		mesh->draw();

	/*	shaders->use();
		Texture::bind(tex, 0);

		shaders->setUniform("u_camera", camera.getMatrix());

		shaders->setUniform("u_transform", t);
		shaders->setUniform("u_tex", (u32)0);

		mesh->draw();

		shaders->stopUsing();
		Texture::bind(nullptr, 0);*/
	}

	const Mesh* mesh;
	const Material* material;
};
} // namespace Dunjun

#endif
