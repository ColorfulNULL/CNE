#pragma once

#include "external.hpp"

#include "../RendererManager/RendererManager.hpp"
#include "../AssetManager/AssetManager.hpp"

namespace cne
{
    // FPS管理器
    class FPSManager
    {
    public:
        using Clock = std::chrono::steady_clock;
        using TimePoint = Clock::time_point;
        using Duration = Clock::duration;

        // 设置最大帧率(-1不限制)
        void SetMaxFPS(int fps);

        // 获取最大帧率(-1不限制)
        int GetMaxFPS();

        // 获取当前帧率
        double GetCurrentFPS();

        // 开始时调用
        void Begin();

        // 结束时调用
        void End();

        FPSManager(const FPSManager&) = delete;
        FPSManager& operator=(const FPSManager&) = delete;
        static FPSManager* Instance()
        {
            if (instance_ == nullptr)
            {
                instance_ = new FPSManager;
            }
            return instance_;
        }
    private:
        int max_fps_ = -1;
        Duration target_duration_ = Duration::zero();
        TimePoint next_frame_time_;
        std::deque<TimePoint> frame_times_;
        double current_fps_ = 0.0;

        FPSManager() = default;
        ~FPSManager() = default;
        static FPSManager* instance_;
    };
}