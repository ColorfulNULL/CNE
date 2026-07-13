#include "RendererManager.hpp"

cne::RendererManager* cne::RendererManager::instance_ = nullptr;

void cne::RendererManager::Init(int w, int h)
{
	renderer_ = SDL_CreateRenderer(WindowManager::Instance()->window_, NULL);
	SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
	SDL_SetRenderLogicalPresentation(renderer_, w, h, SDL_LOGICAL_PRESENTATION_STRETCH);
}

SDL_Renderer* cne::RendererManager::Get()
{
	return renderer_;
}

void cne::RendererManager::SetResolution(int w, int h)
{
	SDL_SetRenderLogicalPresentation(renderer_, w, h, SDL_LOGICAL_PRESENTATION_STRETCH);
}

void cne::RendererManager::Target(SDL_Texture* target)
{
	SDL_SetRenderTarget(renderer_, target);
}

void cne::RendererManager::Begin()
{
	SDL_RenderClear(renderer_);
}

void cne::RendererManager::End()
{
	SDL_RenderPresent(renderer_);
}

void cne::RendererManager::Render(SDL_Texture* texture, SDL_FRect* srcrect, SDL_FRect* dstrect)
{
	SDL_RenderTexture(renderer_, texture, srcrect, dstrect);
}

void cne::RendererManager::Render9Grid(SDL_Texture* texture, const SDL_FRect* srcrect, float left_width, float right_width, float top_height, float bottom_height, float scale, const SDL_FRect* dstrect)
{
	SDL_RenderTexture9Grid(renderer_, texture, srcrect, left_width, right_width, top_height, bottom_height, scale, dstrect);
}

void cne::RendererManager::Render9GridTiled(SDL_Texture* texture, const SDL_FRect* srcrect, float left_width, float right_width, float top_height, float bottom_height, float scale, const SDL_FRect* dstrect, float tileScale)
{
	SDL_RenderTexture9GridTiled(renderer_, texture, srcrect, left_width, right_width, top_height, bottom_height, scale, dstrect, tileScale);
}

void cne::RendererManager::RenderTiled(SDL_Texture* texture, const SDL_FRect* srcrect, float scale, const SDL_FRect* dstrect)
{
	SDL_RenderTextureTiled(renderer_, texture, srcrect, scale, dstrect);
}

void cne::RendererManager::RenderRotated(SDL_Texture* texture, const SDL_FRect* srcrect, const SDL_FRect* dstrect, double angle, const SDL_FPoint* center, SDL_FlipMode flip)
{
	SDL_RenderTextureRotated(renderer_, texture, srcrect, dstrect, angle, center, flip);
}

void cne::RendererManager::SDL_RenderAffine(SDL_Texture* texture, const SDL_FRect* srcrect, const SDL_FPoint* origin, const SDL_FPoint* right, const SDL_FPoint* down)
{
	SDL_RenderTextureAffine(renderer_, texture, srcrect, origin, right, down);
}

void cne::RendererManager::Quit()
{
	SDL_DestroyRenderer(renderer_);
}