#pragma once

#include "external.hpp"

#include "../RendererManager/RendererManager.hpp"
#include "../MixerManager/MixerManager.hpp"
#include "../FileManager/FileManager.hpp"

#include "../../Model/Asset/Image.hpp"
#include "../../Model/Asset/Font.hpp"
#include "../../Model/Asset/Audio.hpp"
#include "../../Model/Asset/Text.hpp"

namespace cne
{
	// 资产管理器
	class AssetManager final
	{
	public:
		// 加载图片资源
		void LoadImage(std::string path, std::string name);

		// 获取图像池中全部名字
		std::vector<std::string> GetImagePoolKey();

		// 获取图像池中全部图像
		std::vector<Image> GetImagePoolValue();

		// 获取图像池长度
		int GetImagePoolSize();

		// 释放图像
		void FreeImage(std::string name);

		// 释放全部图像
		void FreeImagePool();

		// 使用图片
		Image GetImage(std::string name);

		// 查询图像是否存在
		bool IsExistImageKey(std::string name);

		// 加载字体资源
		void LoadFont(std::string path, std::string name);

		// 获取字体池中全部名字
		std::vector<std::string> GetFontPoolKey();

		// 获取字体池中全部字体
		std::vector<Font> GetFontPoolValue();

		// 获取字体池长度
		int GetFontPoolSize();

		// 释放字体
		void FreeFont(std::string name);

		// 释放全部字体
		void FreeFontPool();

		// 获取字体
		Font GetFont(std::string name);

		// 查询字体是否存在
		bool IsExistFontKey(std::string name);

		// 载入音频资源(isPreDecoding=true内存占用大)
		void LoadAudio(std::string path, std::string name, bool isPreDecoding);

		// 获取音频池中全部名字
		std::vector<std::string> GetAudioPoolKey();

		// 获取音频池中全部音频
		std::vector<Audio> GetAudioPoolValue();

		// 获取音频池长度
		int GetAudioPoolSize();

		// 释放音频
		void FreeAudio(std::string name);

		// 释放全部音频
		void FreeAudioPool();

		// 获取音频
		Audio GetAudio(std::string name);

		// 查询音频是否存在
		bool IsExistAudioKey(std::string name);

		// 载入文本表
		void LoadTextMap(std::string path, std::string map_name);

		// 释放文本表
		void FreeTextMapPool();

		// 获取文本表中的文本
		Text GetText(std::string map_name, std::string text_name);

		// 查询文本表是否存在
		bool IsExistTextMapKey(std::string name);

		// 制作临时文字图像
		void MakeTextImage(std::string name, std::string font_name, Text text, int size, SDL_Color color);

		// 获取临时文字图像池中全部名字
		std::vector<std::string> GetTextImagePoolKey();

		// 获取临时文字图像池中全部图像
		std::vector<Image> GetTextImagePoolValue();

		// 释放临时文字图像(具体)
		void FreeTextImage(std::string name);

		// 获取图像池长度
		int GetTextImagePoolSize();

		// 释放临时文字图像(全部)
		void FreeTextImagePool();

		// 使用临时文字图像
		Image GetTextImage(std::string name);

		// 查询临时文字是否存在
		bool IsExistTextImageKey(std::string name);

		AssetManager(const AssetManager&) = delete;
		AssetManager& operator=(const AssetManager&) = delete;
		static AssetManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new AssetManager;
			}
			return instance_;
		}
	private:
		std::map<std::string, Image> image_pool_;
		std::map<std::string, Font> font_pool_;
		std::map<std::string, Audio> audio_pool_;
		std::map<std::string, std::map<std::string, Text>> text_pool_;
		std::map<std::string, Image> image_text_pool_;

		AssetManager() = default;
		~AssetManager() = default;
		static AssetManager* instance_;
	};
}