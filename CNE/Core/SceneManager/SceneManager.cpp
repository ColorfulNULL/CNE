#include "SceneManager.hpp"

cne::SceneManager* cne::SceneManager::instance_ = nullptr;

void cne::SceneManager::Change(Scene* scene)
{
	scene_->Quit();
	delete(scene_);
	scene_ = scene;
	scene_->Init();
}

void cne::SceneManager::Init(Scene* scene)
{
	scene_ = scene;
	scene_->Init();
}

void cne::SceneManager::Update()
{
	scene_->Update();
}

void cne::SceneManager::HandleEvent()
{
	scene_->HandleEvent();
}

void cne::SceneManager::Render()
{
	scene_->Render();
}

void cne::SceneManager::Quit()
{
	scene_->Quit();
	delete(scene_);
}