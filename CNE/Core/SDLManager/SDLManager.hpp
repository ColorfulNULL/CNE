#pragma once

#include "external.hpp"

namespace cne
{
	// SDL管理器
	class SDLManager final
	{
	public:
		// 初始化
		void Init();

		// 关闭
		void Quit();

		SDLManager(const SDLManager&) = delete;
		SDLManager& operator=(const SDLManager&) = delete;
		static SDLManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new SDLManager;
			}
			return instance_;
		}
	private:
		SDLManager() = default;
		~SDLManager() = default;
		static SDLManager* instance_;
	};
}