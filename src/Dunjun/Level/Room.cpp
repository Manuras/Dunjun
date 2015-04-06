#include <Dunjun/Level/Room.hpp>

#include <Dunjun/Scene/MeshRenderer.hpp>

namespace Dunjun
{

Room::Room(Random& random, const Room::Size& size)
: SceneNode()
, size(size)
, material(nullptr)
, m_mesh(nullptr)
, m_random(random)
, m_generated(false)
, m_meshData()
{
}

Room::~Room() { delete m_mesh; }

void Room::generate(bool northDoor,
                    bool eastDoor,
                    bool southDoor,
                    bool westDoor)
{
	if (m_generated)
		return;

	if (!m_mesh)
		m_mesh = new Mesh();

	std::vector<std::vector<TileId>> mapGrid(size.x,
	                                         std::vector<TileId>(size.y));

	TileId emptyTile = {-1, -1};

	TileId lightWoodTile = {0, 11};
	TileId darkWoodTile = {0, 0};
	RandomTileSet stoneTiles;
	for (int i = 1; i < 3; i++)
		stoneTiles.emplace_back(i, 15);
	RandomTileSet darkRockTiles;
	for (int i = 0; i < 4; i++)
		darkRockTiles.emplace_back(i, 0);
	RandomTileSet colorfulTiles;
	for (int i = 3; i < 12; i++)
		colorfulTiles.emplace_back(i, 15);

	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
			mapGrid[i][j] = emptyTile;
	}

	TileId tile = colorfulTiles[m_random.getInt(0, colorfulTiles.size() - 1)];

	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
			mapGrid[i][j] = tile;
	}

	for (int i = 0; i < size.x; i++)
	{
		for (int j = 0; j < size.y; j++)
		{
			if (mapGrid[i][j] != emptyTile)
			{
				addTileSurface(
				    Vector3(i, 0, j), TileSurfaceFace::Up, mapGrid[i][j]);
				addTileSurface(
				    Vector3(i, 3, j), TileSurfaceFace::Down, stoneTiles);
			}
#if 1 // Build Walls
			else
			{
				addTileSurface(
				    Vector3(i, Height, j), TileSurfaceFace::Up, stoneTiles);
			}

			for (int k = 0; k < Height; k++)
			{
				if (mapGrid[i][j] == emptyTile)
				{
					if (i > 0)
					{
						if (mapGrid[i - 1][j] != emptyTile)
							addTileSurface(Vector3(i, k, j),
							               TileSurfaceFace::Left,
							               stoneTiles);
					}

					if (i < size.x - 1)
					{
						if (mapGrid[i + 1][j] != emptyTile)
							addTileSurface(Vector3(i + 1, k, j),
							               TileSurfaceFace::Right,
							               stoneTiles);
					}

					if (j > 0)
					{
						if (mapGrid[i][j - 1] != emptyTile)
							addTileSurface(Vector3(i, k, j),
							               TileSurfaceFace::Back,
							               stoneTiles);
					}

					if (j < size.y - 1)
					{
						if (mapGrid[i][j + 1] != emptyTile)
							addTileSurface(Vector3(i, k, j + 1),
							               TileSurfaceFace::Front,
							               stoneTiles);
					}
				}
				else
				{
					if (i == 0)
					{
						if (westDoor)
						{
							if (j != size.y / 2)
								addTileSurface(Vector3(i, k, j),
								               TileSurfaceFace::Right,
								               stoneTiles);
						}
						else
						{
							addTileSurface(Vector3(i, k, j),
							               TileSurfaceFace::Right,
							               stoneTiles);
						}
					}
					else if (i == size.x - 1)
					{
						if (eastDoor)
						{
							if (j != size.y / 2)
								addTileSurface(Vector3(i + 1, k, j),
								               TileSurfaceFace::Left,
								               stoneTiles);
						}
						else
						{
							addTileSurface(Vector3(i + 1, k, j),
							               TileSurfaceFace::Left,
							               stoneTiles);
						}
					}
					if (j == 0)
					{
						if (northDoor)
						{
							if (i != size.x / 2)
								addTileSurface(Vector3(i, k, j),
								TileSurfaceFace::Front,
								stoneTiles);
						}
						else
						{
							addTileSurface(Vector3(i, k, j),
										   TileSurfaceFace::Front,
										   stoneTiles);
						}
					}
					else if (j == size.y - 1)
					{
						if (southDoor)
						{
							if (i != size.x / 2)
								addTileSurface(Vector3(i, k, j + 1),
								TileSurfaceFace::Back,
								stoneTiles);
						}
						else
						{
							addTileSurface(Vector3(i, k, j + 1),
										   TileSurfaceFace::Back,
										   stoneTiles);
						}
					}
				}
			}
#endif
		}
	}

	m_meshData.generateNormals();
	m_mesh->addData(m_meshData);

	addComponent<MeshRenderer>(m_mesh, material);

	m_generated = true;
}

void Room::addTileSurface(const Vector3& position,
                          TileSurfaceFace face,
                          const TileId& tilePos)
{
	const f32 tileWidth = 1.0f / 16.0f;
	const f32 tileHeight = 1.0f / 16.0f;

	usize index = m_meshData.vertices.size();

	// Right/Left
	if ((u32)face / 2 == 0)
	{
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y + 0.0f, position.z + 1.0f},
		    {(tilePos.x + 1) * tileWidth, (tilePos.y + 0) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y + 0.0f, position.z + 0.0f},
		    {(tilePos.x + 0) * tileWidth, (tilePos.y + 0) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y + 1.0f, position.z + 0.0f},
		    {(tilePos.x + 0) * tileWidth, (tilePos.y + 1) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y + 1.0f, position.z + 1.0f},
		    {(tilePos.x + 1) * tileWidth, (tilePos.y + 1) * tileHeight});
	}
	// Up/Down
	else if ((u32)face / 2 == 1)
	{
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y, position.z + 0.0f},
		    {(tilePos.x + 0) * tileWidth, (tilePos.y + 1) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y, position.z + 1.0f},
		    {(tilePos.x + 0) * tileWidth, (tilePos.y + 0) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 1.0f, position.y, position.z + 1.0f},
		    {(tilePos.x + 1) * tileWidth, (tilePos.y + 0) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 1.0f, position.y, position.z + 0.0f},
		    {(tilePos.x + 1) * tileWidth, (tilePos.y + 1) * tileHeight});
	}
	// Front/Back
	else if ((u32)face / 2 == 2)
	{
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y + 0.0f, position.z + 0.0f},
		    {(tilePos.x + 1) * tileWidth, (tilePos.y + 0) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 1.0f, position.y + 0.0f, position.z + 0.0f},
		    {(tilePos.x + 0) * tileWidth, (tilePos.y + 0) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 1.0f, position.y + 1.0f, position.z + 0.0f},
		    {(tilePos.x + 0) * tileWidth, (tilePos.y + 1) * tileHeight});
		m_meshData.vertices.append(
		    {position.x + 0.0f, position.y + 1.0f, position.z + 0.0f},
		    {(tilePos.x + 1) * tileWidth, (tilePos.y + 1) * tileHeight});
	}

	if ((u32)face % 2 == 0)
		m_meshData.addFace(index, 0, 1, 2).addFace(index, 2, 3, 0);
	else // if ((u32)face % 2 == 1)
		m_meshData.addFace(index, 0, 3, 2).addFace(index, 2, 1, 0);
}

void Room::addTileSurface(const Vector3& position,
                          TileSurfaceFace face,
                          const RandomTileSet& randomTilePosSet)
{
	usize length = randomTilePosSet.size();
	if (length == 0)
		return;
	if (length == 1)
	{
		addTileSurface(position, face, randomTilePosSet[0]);
		return;
	}

	TileId tilePos = randomTilePosSet[m_random.getInt(0, length - 1)];
	addTileSurface(position, face, tilePos);
}

} // namespace Dunjun
