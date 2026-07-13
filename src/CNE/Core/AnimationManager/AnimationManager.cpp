#include "AnimationManager.hpp"

cne::AnimationManager* cne::AnimationManager::instance_ = nullptr;

void cne::AnimationManager::LoadAnimation(std::string name, Animation animation)
{
	animation_pool_.insert(std::make_pair(name, animation));
}

void cne::AnimationManager::FreeAnimation(std::string name)
{
	animation_pool_.erase(name);
}

void cne::AnimationManager::FreeAllAnimation()
{
	animation_pool_.clear();
}

cne::Animation cne::AnimationManager::GetAnimation(std::string name)
{
	return animation_pool_.at(name);
}