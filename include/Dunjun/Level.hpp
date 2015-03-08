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
		TileId() {}

		TileId(s16 x, s16 y)
		: x(x)
		, y(y)
		{
		}

		TileId(s16 xy[2])
		: x(xy[0])
		, y(xy[1])
		{
		}

		inline bool operator==(const TileId& id)
		{
			return (x == id.x) && (y == id.y);
		}

		inline bool operator!=(const TileId& id) { return !operator==(id); }

		s16 x = 0;
		s16 y = 0;
	};

	using RandomTileSet = std::vector<TileId>;

	Level();
	virtual ~Level();

	void addTileSurface(const Vector3& position,
	                    TileSurfaceFace face,
	                    const TileId& tilePos);
	void addTileSurface(const Vector3& position,
	                    TileSurfaceFace face,
	                    const RandomTileSet& randomTilePosSet);

	void generate();

	std::vector<std::vector<TileId>> mapGrid;
	ReadOnly<u16, Level> length = 100;
	ReadOnly<u16, Level> depth = 5;

	const Material* material;
	Mesh* mesh;
	Transform transform;

private:
	Mesh::Data m_meshData;
};
} // namespace Dunjun

#endif
