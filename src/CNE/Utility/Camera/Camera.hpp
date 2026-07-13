#pragma once

#include "external.hpp"

namespace cne
{
    // 2D相机
    class Camera
    {
    public:
        Camera();
        ~Camera() = default;

        // 视口控制（纯数据，无渲染）
        void SetViewport(const SDL_FRect& rect);
        SDL_FRect GetViewport() const;

        // 缩放控制（带平滑过渡）
        void SetPixelsPerMeter(float ppm);          // 直接设置目标缩放
        float GetPixelsPerMeter() const;            // 获取当前实际缩放（考虑插值）
        float GetTargetPixelsPerMeter() const;      // 获取目标缩放
        void ZoomIn(float factor);                  // 放大（factor>1）
        void ZoomOut(float factor);                 // 缩小（factor>1）
        void SetZoomSmoothness(float smoothness);   // 缩放平滑速度（0~1，0为立即）

        // 焦点控制
        void SetFocus(const b2Vec2& worldPos);      // 固定焦点，取消跟随
        b2Vec2 GetFocus() const;                    // 获取当前实际焦点

        // 跟随系统（增强：死区、边界）
        void FollowBody(b2BodyId bodyId, float smoothSpeed = 8.0f);
        void FollowPosition(const b2Vec2* targetPos, float smoothSpeed = 8.0f);
        void StopFollow();
        void SetDeadzone(float width, float height);        // 死区大小（世界单位）
        void SetClampBounds(const b2AABB& bounds);          // 限制相机不能超出边界（世界空间）
        void ClearClampBounds();                            // 取消边界限制

        // 震动系统（增强：波形可选）
        enum ShakeWave { RANDOM, SINE };                    // 震动波形
        void Shake(float intensity, float duration, ShakeWave wave = RANDOM);
        void StopShake();

        // 每帧更新
        void Update(float deltaTime);

        // 坐标转换（无渲染器依赖）
        SDL_FPoint WorldToScreen(const b2Vec2& worldPos) const;
        b2Vec2 ScreenToWorld(const SDL_FPoint& screenPos) const;

    private:
        // 视口（屏幕像素坐标系）
        SDL_FRect viewport_;

        // 缩放（实际值和目标值，支持平滑过渡）
        float pixels_per_meter_;          // 当前实际缩放
        float target_pixels_per_meter_;    // 目标缩放
        float zoom_smoothness_;          // 0~1，1为最平滑

        // 焦点（实际值和目标值）
        b2Vec2 focus_;                  // 当前实际焦点
        b2Vec2 target_focus_;            // 目标焦点（跟随目标或固定点）

        // 跟随系统
        bool is_following_;
        const b2Vec2* follow_target_;    // 外部目标指针
        b2BodyId follow_body_id_;
        bool follow_body_valid_;
        float smooth_speed_;

        // 死区（世界单位）
        float deadzone_w_;               // 0 表示无死区
        float deadzone_h_;
        b2Vec2 deadzone_center_;         // 死区中心（通常为当前焦点）

        // 边界限制（世界空间）
        bool has_clamp_;
        b2AABB clamp_bounds_;

        // 震动系统
        bool is_shaking_;
        float shake_intensity_;
        float shake_decay_rate_;
        float shake_timer_;
        b2Vec2 shake_offset_;
        ShakeWave shake_wave_;
        float shake_phase_;              // 用于正弦波

        // 随机数生成器
        std::mt19937 rng_;
        std::uniform_real_distribution<float> dist_;
    };
}