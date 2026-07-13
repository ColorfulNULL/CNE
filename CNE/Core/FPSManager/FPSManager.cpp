#include "FPSManager.hpp"

cne::FPSManager* cne::FPSManager::instance_ = nullptr;

void cne::FPSManager::SetMaxFPS(int fps)
{
    max_fps_ = fps;
    if (fps > 0)
    {
        target_duration_ = std::chrono::nanoseconds(1'000'000'000 / fps);
    }
    else
    {
        target_duration_ = Duration::zero();
    }
}

int cne::FPSManager::GetMaxFPS()
{
    return max_fps_;
}

double cne::FPSManager::GetCurrentFPS()
{
    return current_fps_;
}

void cne::FPSManager::Begin()
{
    auto now = Clock::now();
    frame_times_.push_back(now);
    auto cutoff = now - std::chrono::seconds(1);
    while (!frame_times_.empty() && frame_times_.front() < cutoff)
    {
        frame_times_.pop_front();
    }
    if (frame_times_.size() >= 2)
    {
        auto duration = now - frame_times_.front();
        double seconds = std::chrono::duration<double>(duration).count();
        if (seconds > 0.0)
        {
            current_fps_ = static_cast<double>(frame_times_.size()) / seconds;
        }
        else
        {
            current_fps_ = 0.0;
        }
    }
    else
    {
        current_fps_ = 0.0;
    }
    if (max_fps_ > 0)
    {
        next_frame_time_ = now + target_duration_;
    }
}

void cne::FPSManager::End()
{
    if (max_fps_ > 0)
    {
        auto now = Clock::now();
        if (now < next_frame_time_)
        {
            std::this_thread::sleep_until(next_frame_time_);
        }
    }
}