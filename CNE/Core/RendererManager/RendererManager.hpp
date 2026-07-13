#pragma once

#include "external.hpp"
#include "../WindowManager/WindowManager.hpp"

namespace cne
{
	// 渲染器管理器
	class RendererManager final
	{
	public:
		friend class EventManager;
		friend class AssetManager;

		// 初始化
		void Init(int w, int h);

		// 获取Renderer
		SDL_Renderer* Get();

		// 设置分辨率
		void SetResolution(int w, int h);

		// 设置目标纹理(NULL表示窗口)
		void Target(SDL_Texture* target);

		// 开始渲染
		void Begin();

		// 结束渲染
		void End();

		// 普通渲染
		void Render(SDL_Texture* texture, SDL_FRect* srcrect, SDL_FRect* dstrect);

		// 9宫格缩放渲染(保持纹理四角不变形，仅拉伸中间区域)
		void Render9Grid
		(
			SDL_Texture* texture,
			const SDL_FRect* srcrect,    // 源纹理中用于9宫格的区域，NULL表示整个纹理
			float left_width,            // 左侧边角宽度
			float right_width,           // 右侧边角宽度
			float top_height,            // 顶部边角高度
			float bottom_height,         // 底部边角高度
			float scale,                 // 边角的缩放倍数，0.0f表示不缩放
			const SDL_FRect* dstrect     // 目标矩形区域，NULL表示整个渲染目标
		);
		// 9宫格平铺渲染(保持纹理四角不变形，中间区域平铺而非拉伸)
		void Render9GridTiled
		(
			SDL_Texture* texture,
			const SDL_FRect* srcrect,    // 源纹理中用于9宫格的区域，NULL表示整个纹理
			float left_width,            // 左侧边角宽度
			float right_width,           // 右侧边角宽度
			float top_height,            // 顶部边角高度
			float bottom_height,         // 底部边角高度
			float scale,                 // 边角的缩放倍数，0.0f表示不缩放
			const SDL_FRect* dstrect,    // 目标矩形区域，NULL表示整个渲染目标
			float tileScale              // 中间区域平铺时的缩放倍数
		);
		// 纹理平铺渲染(将纹理像瓷砖一样重复铺满目标区域)
		void RenderTiled
		(
			SDL_Texture* texture,
			const SDL_FRect* srcrect,    // 作为“瓷砖”的纹理区域，NULL表示整个纹理
			float scale,                 // 瓷砖的缩放倍数
			const SDL_FRect* dstrect     // 需要铺满的目标区域
		);
		// 旋转翻转渲染(对纹理进行旋转和镜像翻转)
		void RenderRotated
		(
			SDL_Texture* texture,
			const SDL_FRect* srcrect,    // 源纹理区域，NULL表示整个纹理
			const SDL_FRect* dstrect,    // 目标矩形区域
			double angle,                // 顺时针旋转的角度（度）
			const SDL_FPoint* center,    // 旋转中心点，NULL则默认为dstrect的中心
			SDL_FlipMode flip            // 翻转模式：SDL_FLIP_NONE, _HORIZONTAL, _VERTICAL
		);

		// 仿射变换渲染(通过映射三个角，实现任意四边形扭曲)
		void SDL_RenderAffine
		(
			SDL_Texture* texture,
			const SDL_FRect* srcrect,    // 源纹理区域，NULL表示整个纹理
			const SDL_FPoint* origin,    // 纹理左上角映射到的目标点
			const SDL_FPoint* right,     // 纹理右上角映射到的目标点
			const SDL_FPoint* down       // 纹理左下角映射到的目标点
		);

		// 关闭
		void Quit();

		RendererManager(const RendererManager&) = delete;
		RendererManager& operator=(const RendererManager&) = delete;
		static RendererManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new RendererManager;
			}
			return instance_;
		}
	private:
		SDL_Renderer* renderer_ = nullptr;

		RendererManager() = default;
		~RendererManager() = default;
		static RendererManager* instance_;
	};
}