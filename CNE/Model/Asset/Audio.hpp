#pragma once

#include "external.hpp"

namespace cne
{
	struct Audio
	{
		MIX_Audio* audio;
		MIX_Track* track;
	};
}