#pragma once

#include "external.hpp"

namespace cne
{
	struct Image
	{
		SDL_Texture* texture;
		float w, h;
	};
}