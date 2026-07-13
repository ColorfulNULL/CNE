#include "Camera.hpp"

cne::Camera::Camera()
    : viewport_{ 0.0f, 0.0f, 800.0f, 600.0f },
    pixels_per_meter_(50.0f),
    target_pixels_per_meter_(50.0f),
    zoom_smoothness_(0.8f),
    focus_{ 0.0f, 0.0f },
    target_focus_{ 0.0f, 0.0f },
    is_following_(false),
    follow_target_(nullptr),
    follow_body_id_(b2_nullBodyId),
    follow_body_valid_(false),
    smooth_speed_(8.0f),
    deadzone_w_(0.0f),
    deadzone_h_(0.0f),
    deadzone_center_{ 0.0f, 0.0f },
    has_clamp_(false),
    clamp_bounds_{ {0,0},{0,0} },
    is_shaking_(false),
    shake_intensity_(0.0f),
    shake_decay_rate_(0.0f),
    shake_timer_(0.0f),
    shake_offset_{ 0.0f, 0.0f },
    shake_wave_(RANDOM),
    shake_phase_(0.0f),
    rng_(std::random_device{}()),
    dist_(-1.0f, 1.0f)
{
}

void cne::Camera::SetViewport(const SDL_FRect& rect)
{
    viewport_ = rect;
}

SDL_FRect cne::Camera::GetViewport() const
{
    return viewport_;
}

void cne::Camera::SetPixelsPerMeter(float ppm)
{
    target_pixels_per_meter_ = std::max(0.1f, ppm);
}

float cne::Camera::GetPixelsPerMeter() const
{
    return pixels_per_meter_;
}

float cne::Camera::GetTargetPixelsPerMeter() const
{
    return target_pixels_per_meter_;
}

void cne::Camera::ZoomIn(float factor)
{
    if (factor > 0.0f)
        target_pixels_per_meter_ *= factor;
}

void cne::Camera::ZoomOut(float factor)
{
    if (factor > 0.0f)
        target_pixels_per_meter_ /= factor;
}

void cne::Camera::SetZoomSmoothness(float smoothness)
{
    zoom_smoothness_ = std::clamp(smoothness, 0.0f, 1.0f);
}

void cne::Camera::SetFocus(const b2Vec2& worldPos)
{
    target_focus_ = worldPos;
    focus_ = worldPos;       // 立即跳转
    StopFollow();
}

b2Vec2 cne::Camera::GetFocus() const
{
    return focus_;
}

void cne::Camera::FollowBody(b2BodyId bodyId, float smoothSpeed)
{
    if (b2Body_IsValid(bodyId))
    {
        follow_body_id_ = bodyId;
        follow_body_valid_ = true;
        follow_target_ = nullptr;
        is_following_ = true;
        smooth_speed_ = std::max(0.1f, smoothSpeed);
        // 瞬间跳到目标
        target_focus_ = b2Body_GetPosition(bodyId);
        focus_ = target_focus_;
        deadzone_center_ = target_focus_;
    }
}

void cne::Camera::FollowPosition(const b2Vec2* targetPos, float smoothSpeed)
{
    if (targetPos)
    {
        follow_target_ = targetPos;
        follow_body_valid_ = false;
        is_following_ = true;
        smooth_speed_ = std::max(0.1f, smoothSpeed);
        target_focus_ = *targetPos;
        focus_ = target_focus_;
        deadzone_center_ = target_focus_;
    }
}

void cne::Camera::StopFollow()
{
    is_following_ = false;
    follow_body_valid_ = false;
    follow_target_ = nullptr;
}

void cne::Camera::SetDeadzone(float width, float height)
{
    deadzone_w_ = std::max(0.0f, width);
    deadzone_h_ = std::max(0.0f, height);
    // 死区中心默认在当前焦点
    deadzone_center_ = focus_;
}

void cne::Camera::SetClampBounds(const b2AABB& bounds)
{
    clamp_bounds_ = bounds;
    has_clamp_ = true;
}

void cne::Camera::ClearClampBounds()
{
    has_clamp_ = false;
}

void cne::Camera::Shake(float intensity, float duration, ShakeWave wave)
{
    if (intensity <= 0.0f || duration <= 0.0f)
    {
        StopShake();
        return;
    }
    is_shaking_ = true;
    shake_intensity_ = intensity;
    shake_decay_rate_ = intensity / std::max(duration, 0.001f);
    shake_timer_ = duration;
    shake_wave_ = wave;
    shake_phase_ = 0.0f;
}

void cne::Camera::StopShake()
{
    is_shaking_ = false;
    shake_intensity_ = 0.0f;
    shake_offset_ = { 0.0f, 0.0f };
    shake_timer_ = 0.0f;
}

void cne::Camera::Update(float deltaTime)
{
    deltaTime = std::min(deltaTime, 0.05f);

    // 1. 更新目标焦点（跟随）
    if (is_following_)
    {
        b2Vec2 newTarget = target_focus_;
        bool hasTarget = false;
        if (follow_body_valid_ && b2Body_IsValid(follow_body_id_))
        {
            newTarget = b2Body_GetPosition(follow_body_id_);
            hasTarget = true;
        }
        else if (follow_target_)
        {
            newTarget = *follow_target_;
            hasTarget = true;
        }
        if (hasTarget)
        {
            // 死区逻辑：如果目标在死区内，焦点不变；否则拉向目标
            if (deadzone_w_ > 0.0f || deadzone_h_ > 0.0f)
            {
                b2Vec2 diff = newTarget - deadzone_center_;
                if (std::abs(diff.x) > deadzone_w_ * 0.5f ||
                    std::abs(diff.y) > deadzone_h_ * 0.5f)
                {
                    // 目标超出死区，将死区中心向目标移动
                    deadzone_center_ += diff * (smooth_speed_ * deltaTime);
                }
                // 死区中心作为真正的跟随目标
                target_focus_ = deadzone_center_;
            }
            else
            {
                target_focus_ = newTarget;
            }
        }
        else
        {
            StopFollow();
        }
    }

    // 2. 平滑焦点插值
    float lerp = 1.0f - std::exp(-smooth_speed_ * deltaTime);
    focus_.x += (target_focus_.x - focus_.x) * lerp;
    focus_.y += (target_focus_.y - focus_.y) * lerp;

    // 3. 边界钳制
    if (has_clamp_)
    {
        // 计算当前视口在世界空间的一半大小
        float halfW = (viewport_.w * 0.5f) / pixels_per_meter_;
        float halfH = (viewport_.h * 0.5f) / pixels_per_meter_;
        b2Vec2 minFocus = { clamp_bounds_.lowerBound.x + halfW,
                           clamp_bounds_.lowerBound.y + halfH };
        b2Vec2 maxFocus = { clamp_bounds_.upperBound.x - halfW,
                           clamp_bounds_.upperBound.y - halfH };
        focus_.x = std::clamp(focus_.x, minFocus.x, maxFocus.x);
        focus_.y = std::clamp(focus_.y, minFocus.y, maxFocus.y);
        // 同步目标焦点（防止累积误差）
        target_focus_ = focus_;
    }

    // 4. 缩放平滑
    if (zoom_smoothness_ > 0.0f)
    {
        float zoomLerp = 1.0f - std::exp(-zoom_smoothness_ * deltaTime * 5.0f);
        pixels_per_meter_ += (target_pixels_per_meter_ - pixels_per_meter_) * zoomLerp;
    }
    else
    {
        pixels_per_meter_ = target_pixels_per_meter_;
    }

    // 5. 震动
    if (is_shaking_)
    {
        shake_timer_ -= deltaTime;
        if (shake_timer_ <= 0.0f)
        {
            StopShake();
            return;
        }
        shake_intensity_ -= shake_decay_rate_ * deltaTime;
        if (shake_intensity_ <= 0.1f)
        {
            StopShake();
            return;
        }

        if (shake_wave_ == RANDOM)
        {
            float angle = dist_(rng_) * 2.0f * 3.14159265f;
            float mag = shake_intensity_ * (0.8f + 0.2f * dist_(rng_));
            shake_offset_.x = std::cos(angle) * mag;
            shake_offset_.y = std::sin(angle) * mag;
        }
        else // SINE
        {
            shake_phase_ += deltaTime * 50.0f; // 频率可调
            float mag = shake_intensity_ * 0.7f;
            shake_offset_.x = std::sin(shake_phase_) * mag;
            shake_offset_.y = std::cos(shake_phase_ * 0.7f) * mag;
        }
    }
    else
    {
        shake_offset_ = { 0.0f, 0.0f };
    }
}

SDL_FPoint cne::Camera::WorldToScreen(const b2Vec2& worldPos) const
{
    b2Vec2 eff = focus_ + shake_offset_;
    float dx = worldPos.x - eff.x;
    float dy = eff.y - worldPos.y;   // Y轴翻转
    float sx = viewport_.x + viewport_.w * 0.5f + dx * pixels_per_meter_;
    float sy = viewport_.y + viewport_.h * 0.5f + dy * pixels_per_meter_;
    return { sx, sy };
}

b2Vec2 cne::Camera::ScreenToWorld(const SDL_FPoint& screenPos) const
{
    b2Vec2 eff = focus_ + shake_offset_;
    float dx = (screenPos.x - (viewport_.x + viewport_.w * 0.5f)) / pixels_per_meter_;
    float dy = (screenPos.y - (viewport_.y + viewport_.h * 0.5f)) / pixels_per_meter_;
    float worldX = eff.x + dx;
    float worldY = eff.y - dy;
    return { worldX, worldY };
}