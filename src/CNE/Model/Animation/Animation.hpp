#pragma once

#include "external.hpp"

#include "../Tile/Tile.hpp"

namespace cne
{
	struct Animation
	{
		std::vector<Tile> tile_list;
		int index;
		int interval;
	};
}