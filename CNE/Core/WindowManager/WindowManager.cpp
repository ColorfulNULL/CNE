#include "WindowManager.hpp"

cne::WindowManager* cne::WindowManager::instance_ = nullptr;

void cne::WindowManager::Init(std::string title, SDL_Rect rect)
{
	window_ = SDL_CreateWindow(title.c_str(), rect.w, rect.h, SDL_WINDOW_TRANSPARENT | SDL_WINDOW_RESIZABLE);
	SDL_SetWindowPosition(window_, rect.x, rect.y);
}

SDL_Window* cne::WindowManager::Get()
{
	return window_;
}

void cne::WindowManager::SetIcon(std::string path)
{
	SDL_Surface* icon = IMG_Load(path.c_str());
	SDL_SetWindowIcon(window_, icon);
	SDL_DestroySurface(icon);
}

void cne::WindowManager::SetIcon(SDL_Surface* icon)
{
	SDL_SetWindowIcon(window_, icon);
}

void cne::WindowManager::SetTitle(std::string title)
{
	SDL_SetWindowTitle(window_, title.c_str());
}

std::string cne::WindowManager::GetTitle()
{
	return std::string(SDL_GetWindowTitle(window_));
}

void cne::WindowManager::SetRect(SDL_Rect rect)
{
	SDL_SetWindowPosition(window_, rect.x, rect.y);
	SDL_SetWindowSize(window_, rect.w, rect.h);
}

SDL_Rect cne::WindowManager::GetRect()
{
	SDL_Rect rect;
	SDL_GetWindowPosition(window_, &rect.x, &rect.y);
	SDL_GetWindowSize(window_, &rect.w, &rect.h);
	return rect;
}

void cne::WindowManager::GetPixelsSize(int& w, int& h)
{
	SDL_GetWindowSizeInPixels(window_, &w, &h);
}

void cne::WindowManager::SetShape(std::string path)
{
	SDL_Surface* shape = IMG_Load(path.c_str());
	SDL_SetWindowShape(window_, shape);
	SDL_DestroySurface(shape);
}

void cne::WindowManager::SetShape(SDL_Surface* shape)
{
	SDL_SetWindowShape(window_, shape);
}

void cne::WindowManager::SetOpacity(float opacity)
{
	SDL_SetWindowOpacity(window_, opacity);
}

float cne::WindowManager::GetOpacity()
{
	return SDL_GetWindowOpacity(window_);
}

void cne::WindowManager::SetFull(bool isFull)
{
	SDL_SetWindowFullscreen(window_, isFull);
}

void cne::WindowManager::ChangeFull()
{
	if (SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN)
	{
		SDL_SetWindowFullscreen(window_, false);
	}
	else
	{
		SDL_SetWindowFullscreen(window_, true);
	}
}

bool cne::WindowManager::IsFull()
{
	return SDL_GetWindowFlags(window_) & SDL_WINDOW_FULLSCREEN;
}

void cne::WindowManager::SetBordered(bool isBordered)
{
	SDL_SetWindowBordered(window_, isBordered);
}

void cne::WindowManager::ChangeBordered()
{
	if (SDL_GetWindowFlags(window_) & SDL_WINDOW_BORDERLESS)
	{
		SDL_SetWindowBordered(window_, false);
	}
	else
	{
		SDL_SetWindowBordered(window_, true);
	}
}

bool cne::WindowManager::IsBordered()
{
	return SDL_GetWindowFlags(window_) & SDL_WINDOW_BORDERLESS;
}

void cne::WindowManager::SetAlwaysOnTop(bool isAlwaysOnTop)
{
	SDL_SetWindowAlwaysOnTop(window_, isAlwaysOnTop);
}

void cne::WindowManager::ChangeAlwaysOnTop()
{
	if (SDL_GetWindowFlags(window_) & SDL_WINDOW_ALWAYS_ON_TOP)
	{
		SDL_SetWindowAlwaysOnTop(window_, false);
	}
	else
	{
		SDL_SetWindowAlwaysOnTop(window_, true);
	}
}

bool cne::WindowManager::IsAlwaysOnTop()
{
	return SDL_GetWindowFlags(window_) & SDL_WINDOW_ALWAYS_ON_TOP;
}

void cne::WindowManager::Hide()
{
	SDL_HideWindow(window_);
}

void cne::WindowManager::Show()
{
	SDL_ShowWindow(window_);
}

bool cne::WindowManager::IsShow()
{
	return (SDL_GetWindowFlags(window_) & SDL_WINDOW_HIDDEN) == 0;
}

void cne::WindowManager::Max()
{
	SDL_MaximizeWindow(window_);
}

bool cne::WindowManager::IsMax()
{
	return SDL_GetWindowFlags(window_) & SDL_WINDOW_MAXIMIZED;
}

void cne::WindowManager::Min()
{
	SDL_MinimizeWindow(window_);
}

bool cne::WindowManager::IsMin()
{
	return SDL_GetWindowFlags(window_) & SDL_WINDOW_MINIMIZED;
}

void cne::WindowManager::Raise()
{
	SDL_RaiseWindow(window_);
}

void cne::WindowManager::Restore()
{
	SDL_RestoreWindow(window_);
}

void cne::WindowManager::GrabMouse(bool isGrab)
{
	SDL_SetWindowMouseGrab(window_, isGrab);
}

void cne::WindowManager::GrabKeyboard(bool isGrab)
{
	SDL_SetWindowKeyboardGrab(window_, isGrab);
}

bool cne::WindowManager::IsGrabMouse()
{
	return SDL_GetWindowMouseGrab(window_);
}

bool cne::WindowManager::IsGrabKeyboard()
{
	return SDL_GetWindowKeyboardGrab(window_);
}

void cne::WindowManager::Quit()
{
	SDL_DestroyWindow(window_);
}