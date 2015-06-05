#ifndef DUNJUN_GRAPHICS_MODELASSET_HPP
#define DUNJUN_GRAPHICS_MODELASSET_HPP

#include <Dunjun/Graphics/Material.hpp>
#include <Dunjun/Graphics/Mesh.hpp>

namespace Dunjun
{
struct ModelAsset
{
	Material* material{nullptr};
	const Mesh* mesh{nullptr};
};
} // namespace Dunjun

#endif
