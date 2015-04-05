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
	Material material;

	std::vector<Room*> rooms;

private:
	void placeRooms(int floor);

	Random m_random;

};
} // namespace Dunjun

#endif
