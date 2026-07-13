#include "Timer.hpp"

cne::Timer::Timer(int intervalMs)
    : interval_(std::chrono::milliseconds(intervalMs))
    , active_(true)
{
    next_trigger_time_ = Clock::now() + interval_;
}

void cne::Timer::SetCallback(std::function<void()> callback)
{
    callback_ = std::move(callback);
}

bool cne::Timer::IsTimeUp()
{
    bool ret = triggered_;
    triggered_ = false;
    return ret;
}

void cne::Timer::Update()
{
    if (!active_ || paused_) return;

    auto now = Clock::now();
    while (now >= next_trigger_time_)
    {
        if (callback_)
        {
            callback_();
        }
        triggered_ = true;
        next_trigger_time_ += interval_;
    }
}

void cne::Timer::Pause()
{
    if (!paused_ && active_)
    {
        paused_ = true;
        pause_start_ = Clock::now();
    }
}

void cne::Timer::Resume()
{
    if (paused_ && active_)
    {
        auto now = Clock::now();
        auto pause_duration = now - pause_start_;
        next_trigger_time_ += pause_duration;
        paused_ = false;
    }
}

bool cne::Timer::IsRunning() const
{
    return active_ && !paused_;
}

void cne::Timer::SetInterval(int intervalMs)
{
    interval_ = std::chrono::milliseconds(intervalMs);
    active_ = true;
    paused_ = false;
    triggered_ = false;
    next_trigger_time_ = Clock::now() + interval_;
}