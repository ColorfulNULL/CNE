#pragma once

#include "external.hpp"

#include "../../Model/Animation/Animation.hpp"

namespace cne
{
	// 动画管理器
	class AnimationManager final
	{
	public:
		// 载入动画
		void LoadAnimation(std::string name, Animation animation);

		// 移除动画
		void FreeAnimation(std::string name);

		// 移除全部动画
		void FreeAllAnimation();

		// 获取动画
		Animation GetAnimation(std::string name);

		AnimationManager(const AnimationManager&) = delete;
		AnimationManager& operator=(const AnimationManager&) = delete;
		static AnimationManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new AnimationManager;
			}
			return instance_;
		}
	private:
		std::map<std::string, Animation> animation_pool_;

		AnimationManager() = default;
		~AnimationManager() = default;
		static AnimationManager* instance_;
	};
}