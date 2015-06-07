#ifndef DUNJUN_CONTEXT_HPP
#define DUNJUN_CONTEXT_HPP

#include <Dunjun/Window/Window.hpp>
#include <Dunjun/ResourceHolders.hpp>

namespace Dunjun
{
struct Context
{
	explicit Context(Window& window,
	                 TextureHolder& textureHolder,
	                 ShaderHolder& shaderHolder,
	                 MeshHolder& meshHolder,
	                 MaterialHolder& materialHolder)
	: window{window}
	, textureHolder{textureHolder}
	, shaderHolder{shaderHolder}
	, meshHolder{meshHolder}
	, materialHolder{materialHolder}
	{
	}

	Context(const Context&) = default;

	Window& window;
	TextureHolder& textureHolder;
	ShaderHolder& shaderHolder;
	MeshHolder& meshHolder;
	MaterialHolder& materialHolder;
};
} // namespace Dunjun

#endif
