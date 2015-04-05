#ifndef DUNJUN_MODELASSET_HPP
#define DUNJUN_MODELASSET_HPP

#include <Dunjun/Material.hpp>
#include <Dunjun/Mesh.hpp>

namespace Dunjun
{
struct ModelAsset
{
	Material material;
	const Mesh* mesh;
};
} // namespace Dunjun

#endif
