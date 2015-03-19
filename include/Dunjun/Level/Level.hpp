#ifndef DUNJUN_LEVEL_LEVEL_HPP
#define DUNJUN_LEVEL_LEVEL_HPP

#include <Dunjun/Common.hpp>
#include <Dunjun/Math/Random.hpp>
#include <Dunjun/Level/Room.hpp>
#include <Dunjun/Scene/SceneNode.hpp>

#include <vector>

namespace Dunjun
{
class Level : public SceneNode
{
public:
	Level();

	void generate();

	Transform transform;
	Material* material;

private:
	void placeRooms();

	Random m_random;
	std::vector<Room> m_rooms;
};
} // namespace Dunjun

#endif
