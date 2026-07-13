#pragma once

#include "external.hpp"
#include "../../Model/Scene/Scene.hpp"

namespace cne
{
	// 界面管理器
	class SceneManager final
	{
	public:
		// 切换窗口
		void Change(cne::Scene* scene);

		// 初始化
		void Init(cne::Scene* scene);

		// 更新数据
		void Update();

		// 事件处理
		void HandleEvent();

		// 渲染画面
		void Render();

		// 关闭
		void Quit();

		SceneManager(const SceneManager&) = delete;
		SceneManager& operator=(const SceneManager&) = delete;
		static SceneManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new SceneManager;
			}
			return instance_;
		}
	private:
		cne::Scene* scene_ = nullptr;

		SceneManager() = default;
		~SceneManager() = default;
		static SceneManager* instance_;
	};
}