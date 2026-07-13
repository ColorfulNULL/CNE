#pragma once

#include "external.hpp"

namespace cne
{
	// 混音器管理器
	class MixerManager final
	{
	public:
		friend class AssetManager;

		// 初始化
		void Init();

		// 获取混音器
		MIX_Mixer* Get();

		// 播放
		void Play(MIX_Track* track, int loops);

		// 播放
		void Play(MIX_Track* track, int loops, Sint64 ms);

		// 停止
		void Stop(MIX_Track* track, Sint64 ms);

		// 是否播放
		bool IsPlay(MIX_Track* track);
		
		// 获取淡入淡出数据
		Sint64 GetFade(MIX_Track* track);// 返回值小于 0 表示正在淡出，大于 0 表示正在淡入

		// 暂停
		void Pause(MIX_Track* track);

		// 恢复
		void Resume(MIX_Track* track);

		// 是否暂停
		bool IsPause(MIX_Track* track);

		// 跳转(秒s)
		void SetPosition(MIX_Track* track, Sint64 ms);

		// 获取当前播放位置
		Sint64 GetPosition(MIX_Track* track);

		// 音量全局控制（0 = 静音，128 = 正常音量）
		void SetAllVolume(float volume);

		// 音量音轨控制（0 = 静音，128 = 正常音量）
		void SetVolume(float volume, MIX_Track* track);

		// 关闭
		void Quit();

		MixerManager(const MixerManager&) = delete;
		MixerManager& operator=(const MixerManager&) = delete;
		static MixerManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new MixerManager;
			}
			return instance_;
		}
	private:
		MIX_Mixer* mixer_ = nullptr;

		MixerManager() = default;
		~MixerManager() = default;
		static MixerManager* instance_;
	};
}