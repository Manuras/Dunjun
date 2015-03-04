#include <Dunjun/Level.hpp>
#include <cstdlib>

namespace Dunjun
{
Level::Level() 
{}

Level::~Level()
{
	delete mesh;
}

void Level::generate()
{
	if (!mesh)
		mesh = new Mesh();

	mesh->addData(m_meshData);
}

void Level::addTileSurface(const Vector3& position,
                           TileSurfaceFace face,
                           const TileId& tilePos)
{
	if (!mesh)
		mesh = new Mesh();

	const f32 tileWidth = 1.0f / 16.0f;
	const f32 tileHeight = 1.0f / 16.0f;

	usize index = m_meshData.vertices.size();

	// Right/Left
	if ((u32)face / 2 == 0)
	{
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y + 0.0f, position.z + 1.0f},
		     {(tilePos.x + 1) * tileWidth, (tilePos.y + 0) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y + 0.0f, position.z + 0.0f},
		     {(tilePos.x + 0) * tileWidth, (tilePos.y + 0) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y + 1.0f, position.z + 0.0f},
		     {(tilePos.x + 0) * tileWidth, (tilePos.y + 1) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y + 1.0f, position.z + 1.0f},
		     {(tilePos.x + 1) * tileWidth, (tilePos.y + 1) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
	}
	// Up/Down
	else if ((u32)face / 2 == 1)
	{
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y, position.z + 0.0f},
		     {(tilePos.x + 0) * tileWidth, (tilePos.y + 1) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y, position.z + 1.0f},
		     {(tilePos.x + 0) * tileWidth, (tilePos.y + 0) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 1.0f, position.y, position.z + 1.0f},
		     {(tilePos.x + 1) * tileWidth, (tilePos.y + 0) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 1.0f, position.y, position.z + 0.0f},
		     {(tilePos.x + 1) * tileWidth, (tilePos.y + 1) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
	}
	// Front/Back
	else if ((u32)face / 2 == 2)
	{
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y + 0.0f, position.z + 0.0f},
		     {(tilePos.x + 1) * tileWidth, (tilePos.y + 0) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 1.0f, position.y + 0.0f, position.z + 0.0f},
		     {(tilePos.x + 0) * tileWidth, (tilePos.y + 0) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 1.0f, position.y + 1.0f, position.z + 0.0f},
		     {(tilePos.x + 0) * tileWidth, (tilePos.y + 1) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
		m_meshData.vertices.push_back(
		    {{position.x + 0.0f, position.y + 1.0f, position.z + 0.0f},
		     {(tilePos.x + 1) * tileWidth, (tilePos.y + 1) * tileHeight},
		     {{0xFF, 0xFF, 0xFF, 0xFF}}});
	}

	if ((u32)face % 2 == 0)
	{
		m_meshData.indices.push_back(index + 0);
		m_meshData.indices.push_back(index + 1);
		m_meshData.indices.push_back(index + 2);
		m_meshData.indices.push_back(index + 2);
		m_meshData.indices.push_back(index + 3);
		m_meshData.indices.push_back(index + 0);
	}
	else // if ((u32)face % 2 == 1)
	{
		m_meshData.indices.push_back(index + 0);
		m_meshData.indices.push_back(index + 3);
		m_meshData.indices.push_back(index + 2);
		m_meshData.indices.push_back(index + 2);
		m_meshData.indices.push_back(index + 1);
		m_meshData.indices.push_back(index + 0);
	}
}

void Level::addTileSurface(const Vector3& position,
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
	// TODO(bill): use better randomizer
	TileId tilePos = randomTilePosSet[rand() % length];
	addTileSurface(position, face, tilePos);
}
} // namespace Dunjun
