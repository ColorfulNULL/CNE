#include "SDLManager.hpp"

cne::SDLManager* cne::SDLManager::instance_ = nullptr;

void cne::SDLManager::Init()
{
	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
	TTF_Init();
	MIX_Init();
}

void cne::SDLManager::Quit()
{
	MIX_Quit();
	TTF_Quit();
	SDL_Quit();
}