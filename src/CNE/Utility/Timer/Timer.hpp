#pragma once

#include "external.hpp"

namespace cne
{
    // 计时器
    class Timer
    {
    public:
        using Clock = std::chrono::steady_clock;
        using TimePoint = Clock::time_point;
        using Duration = Clock::duration;

        // 默认构造函数（间隔为 0，未激活）
        Timer() = default;

        // 构造，传入间隔（毫秒），自动开始运行
        explicit Timer(int intervalMs);

        // 设置回调函数（可多次调用，覆盖之前的）
        void SetCallback(std::function<void()> callback);

        // 返回是否触发（自上次调用此函数后，如果触发过则返回 true，并清除标志）
        bool IsTimeUp();

        // 更新计时，如果到达间隔则触发回调并重置下一次触发时间
        void Update();

        // 暂停计时
        void Pause();

        // 恢复计时
        void Resume();

        // 是否正在运行（即未暂停）
        bool IsRunning() const;

        // 重新设置间隔（毫秒），会重置计时器
        void SetInterval(int intervalMs);

    private:
        Duration interval_ = Duration::zero();
        TimePoint next_trigger_time_;
        TimePoint pause_start_;
        bool paused_ = false;
        bool triggered_ = false;
        bool active_ = false;        // 是否已设置有效间隔
        std::function<void()> callback_;
    };
}