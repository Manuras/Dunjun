#ifndef DUNJUN_RESOURCEHOLDERS_HPP
#define DUNJUN_RESOURCEHOLDERS_HPP

#include <Dunjun/ResourceHolder.hpp>
#include <Dunjun/Graphics.hpp>

namespace Dunjun
{
class TextureHolder : public ResourceHolder<Texture, std::string>
{
public:
	bool insertFromFile(const std::string& id,
	                    const std::string& filename,
	                    TextureFilter minMagFilter = TextureFilter::Linear,
	                    TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge)
	{
		std::unique_ptr<Texture> tex{make_unique<Texture>()};
		bool t{tex->loadFromFile(BaseDirectory::Textures + filename, minMagFilter, wrapMode)};
		if (t)
			insert(id, std::move(tex));
		return t;
	}

	bool
	    insertFromImage(const std::string& id,
	                    const Image& image,
	                    TextureFilter minMagFilter = TextureFilter::Linear,
	                    TextureWrapMode wrapMode = TextureWrapMode::ClampToEdge)
	{
		std::unique_ptr<Texture> tex{make_unique<Texture>()};
		bool t{tex->loadFromImage(image, minMagFilter, wrapMode)};
		if (t)
			insert(id, std::move(tex));

		return t;
	}
};

class ShaderHolder : public ResourceHolder<ShaderProgram, std::string>
{
public:
	bool insertFromFile(const std::string& id,
	                    const std::string& vertexFilename,
	                    const std::string& fragmentFilename,
	                    bool bindDefaultAttribLocation = true)
	{
		std::unique_ptr<ShaderProgram> shaders{make_unique<ShaderProgram>()};
		if (!shaders->attachShaderFromFile(ShaderType::Vertex, vertexFilename))
		{
			std::cerr << shaders->getErrorLog() << std::endl;

			return false;
		}
		if (!shaders->attachShaderFromFile(ShaderType::Fragment,
		                                   fragmentFilename))
		{
			std::cerr << shaders->getErrorLog() << std::endl;

			return false;
		}

		if (bindDefaultAttribLocation)
		{
			shaders->bindAttribLocation((u32)AtrribLocation::Position,
			                            "a_position");
			shaders->bindAttribLocation((u32)AtrribLocation::TexCoord,
			                            "a_texCoord");
			shaders->bindAttribLocation((u32)AtrribLocation::Color, "a_color");
			shaders->bindAttribLocation((u32)AtrribLocation::Normal,
			                            "a_normal");
		}

		if (!shaders->link())
		{
			std::cerr << shaders->getErrorLog() << std::endl;

			return false;
		}

		insert(id, std::move(shaders));

		return true;
	}
};

using MeshHolder = ResourceHolder<Mesh, std::string>;
using MaterialHolder = ResourceHolder<Material, std::string>;

extern TextureHolder g_textureHolder;
extern ShaderHolder g_shaderHolder;
extern MeshHolder g_meshHolder;
extern MaterialHolder g_materialHolder;
} // namespace Dunjun

#endif
