#pragma once

#include "external.hpp"

namespace cne
{
	struct Tile
	{
		std::string image_key;
		SDL_FRect srcrect;
		double direction;
	};
}