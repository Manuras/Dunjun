#include <Dunjun/Level/Level.hpp>

namespace Dunjun
{
Level::Level()
: m_random(1337)
, rooms()
{
}

void Level::generate()
{
	//placeRooms(-1);
	placeRooms(0);
	//placeRooms(1);
}

void Level::placeRooms(int floor)
{
	if (material == nullptr)
	{
		std::cout << "Level::placeRooms material == nullptr\n";
		return;
	}

	// m_random.setSeed(1);

	const int w = 100;
	const int h = 100;
	const Room::Size size(9, 9);

	//transform.position.x = -(w - 0.5f) * size.x / 2.0f;
	//transform.position.z = -(h - 0.5f) * size.y / 2.0f;


	bool grid[w][h] = {{false}};

	grid[w / 2][h / 2] = true;

	// 2 Random walks from center;
	for (int r = 0; r < 4; r++)
	{
		int x = w / 2;
		int y = h / 2;

		int prevX = w / 2;
		int prevY = h / 2;
		// random walk from center
		for (int n = 0; n < 10; n++)
		{
			int d = m_random.getInt(0, 3);

			for (int l = 0; l < 3; l++)
			{
				switch (d)
				{
				case 0: // right
					x++;
					break;
				case 1: // up
					y++;
					break;
				case 2: // left
					x--;
					break;
				case 3: // down
					y--;
					break;
				}

				x = Math::clamp(x, 0, w - 1);
				y = Math::clamp(y, 0, h - 1);

				if (grid[x][y])
				{
					x = prevX;
					y = prevY;
					continue;
				}

				grid[x][y] = true;
				prevX = x;
				prevY = y;
			}
		}
	}

	// random off shoots
	{
		for (int shoot = 0; shoot < 10; shoot++)
		{
			while (true)
			{
				int x = m_random.getInt(0, w - 1);
				int y = m_random.getInt(0, h - 1);

				if (grid[x][y])
				{
					int d = m_random.getInt(0, 3);

					switch (d)
					{
					case 0: // right
						x++;
						break;
					case 1: // up
						y++;
						break;
					case 2: // left
						x--;
						break;
					case 3: // down
						y--;
						break;
					}

					x = Math::clamp(x, 0, w - 1);
					y = Math::clamp(y, 0, h - 1);

					if (grid[x][y])
						continue;

					grid[x][y] = true;
					break;
				}
			}
		}
	}

	int roomCount = 0;

	for (int i = 0; i < w; i++)
	{
		for (int j = 0; j < h; j++)
		{
			if (grid[i][j] == false)
				continue;

			auto room = make_unique<Room>(m_random, size);

			room->transform.position.x = size.x * (i - w/2);
			room->transform.position.y = Room::Height * floor;
			room->transform.position.z = size.y * (j - h/2);

			room->material = material;

			bool northDoor = false;
			bool eastDoor  = false;
			bool southDoor = false;
			bool westDoor  = false;
				
			if (i != 0 && grid[i - 1][j])
				westDoor = true;
			if (i != w - 1 && grid[i + 1][j])
				eastDoor = true;

			if (j != 0 && grid[i][j - 1])
				northDoor = true;
			if (j != h - 1 && grid[i][j + 1])
				southDoor = true;

			room->generate(northDoor,
						   eastDoor,
						   southDoor,
						   westDoor);

			rooms.push_back(room.get());

			attachChild(std::move(room));
			roomCount++;
		}
	}

	std::cout << roomCount << std::endl;
}
} // namespace Dunjun
