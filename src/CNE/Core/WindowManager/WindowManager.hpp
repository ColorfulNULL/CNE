#pragma once

#include "external.hpp"

namespace cne
{
	// 窗口管理器
	class WindowManager final
	{
	public:
		friend class RendererManager;
		friend class EventManager;

		// 初始化
		void Init(std::string title, SDL_Rect rect);

		// 获取Window
		SDL_Window* Get();

		// 设置ICON
		void SetIcon(std::string path);

		// 设置ICON
		void SetIcon(SDL_Surface* icon);

		// 设置标题
		void SetTitle(std::string title);

		// 获取标题
		std::string GetTitle();

		// 设置窗口矩形
		void SetRect(SDL_Rect rect);

		// 获取窗口矩形
		SDL_Rect GetRect();

		// 获取窗口像素
		void GetPixelsSize(int& w, int& h);

		// 设置形状
		void SetShape(std::string path);

		// 设置形状
		void SetShape(SDL_Surface* shape);

		// 设置透明度(0.0f~1.0f)
		void SetOpacity(float opacity);

		// 获取透明度(0.0f~1.0f)
		float GetOpacity();

		// 设置全屏
		void SetFull(bool isFull);

		// 切换全屏
		void ChangeFull();

		// 是否全屏
		bool IsFull();

		// 设置边框
		void SetBordered(bool isBordered);

		// 切换边框
		void ChangeBordered();

		// 是否边框
		bool IsBordered();

		// 设置置顶
		void SetAlwaysOnTop(bool isAlwaysOnTop);

		// 切换置顶
		void ChangeAlwaysOnTop();

		// 是否置顶
		bool IsAlwaysOnTop();

		// 隐藏
		void Hide();

		// 显示
		void Show();

		// 是否显示
		bool IsShow();

		// 最大化
		void Max();

		// 是否最大化
		bool IsMax();

		// 最小化
		void Min();

		// 是否最小化
		bool IsMin();

		// 提升到最前
		void Raise();

		// 恢复窗口
		void Restore();

		// 捕获鼠标
		void GrabMouse(bool isGrab);

		// 捕获键盘
		void GrabKeyboard(bool isGrab);

		// 是否捕获鼠标
		bool IsGrabMouse();

		// 是否捕获键盘
		bool IsGrabKeyboard();

		// 关闭
		void Quit();

		WindowManager(const WindowManager&) = delete;
		WindowManager& operator=(const WindowManager&) = delete;
		static WindowManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new WindowManager;
			}
			return instance_;
		}
	private:
		SDL_Window* window_ = nullptr;

		WindowManager() = default;
		~WindowManager() = default;
		static WindowManager* instance_;
	};
}