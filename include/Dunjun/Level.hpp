#ifndef DUNJUN_LEVEL_HPP
#define DUNJUN_LEVEL_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/ModelAsset.hpp>

#include <vector>

namespace Dunjun
{
class Level
{
public:
	enum class TileSurfaceFace : u32
	{
		Right = 0,
		Left = 1,
		Up = 2,
		Down = 3,
		Front = 4,
		Back = 5,
	};

	struct TileId
	{
		u16 x;
		u16 y;
	};

	using RandomTileSet = std::vector<TileId>;


	Level();
	virtual ~Level();

	void addTileSurface(const Vector3& position, TileSurfaceFace face, const TileId& tilePos);
	void addTileSurface(const Vector3& position, TileSurfaceFace face, const RandomTileSet& randomTilePosSet);

	void generate();

	const Material* material;
	Mesh* mesh;
	Transform transform;

private:
	Mesh::Data m_meshData;
	
};
} // namespace Dunjun

#endif
