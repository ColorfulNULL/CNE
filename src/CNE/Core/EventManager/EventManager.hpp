#pragma once

#include "external.hpp"

#include "../WindowManager/WindowManager.hpp"
#include "../RendererManager/RendererManager.hpp"

namespace cne
{
    // 事件管理器
    class EventManager
    {
    public:
        // 回调类型
        using MouseMotionCallback = std::function<void(const SDL_MouseMotionEvent&)>;
        using MouseButtonCallback = std::function<void(const SDL_MouseButtonEvent&)>;
        using MouseWheelCallback = std::function<void(const SDL_MouseWheelEvent&)>;
        using KeyboardCallback = std::function<void(const SDL_KeyboardEvent&)>;
        using TextInputCallback = std::function<void(const SDL_TextInputEvent&)>;
        using TextEditingCallback = std::function<void(const SDL_TextEditingEvent&)>;
        using GamepadDeviceCallback = std::function<void(const SDL_GamepadDeviceEvent&)>;
        using GamepadButtonCallback = std::function<void(const SDL_GamepadButtonEvent&)>;
        using GamepadAxisCallback = std::function<void(const SDL_GamepadAxisEvent&)>;
        using WindowCallback = std::function<void(const SDL_WindowEvent&)>;
        using QuitCallback = std::function<void(const SDL_QuitEvent&)>;

        // 初始化
        void Init();

        // 回调注册
        void RegisterMouseMotion(MouseMotionCallback cb);
        void RegisterMouseButton(MouseButtonCallback cb);
        void RegisterMouseWheel(MouseWheelCallback cb);
        void RegisterKeyboard(KeyboardCallback cb);
        void RegisterTextInput(TextInputCallback cb);
        void RegisterTextEditing(TextEditingCallback cb);
        void RegisterGamepadDevice(GamepadDeviceCallback cb);
        void RegisterGamepadButton(GamepadButtonCallback cb);
        void RegisterGamepadAxis(GamepadAxisCallback cb);
        void RegisterWindow(WindowCallback cb);
        void RegisterQuit(QuitCallback cb);
        void ClearCallbacks();

        // ImGui
        void SetImGuiHandlingEnabled(bool enabled);
        void SetBlockOnImGuiCapture(bool block);

        // 事件类型启用
        void SetEventTypeEnabled(uint32_t type, bool enabled);
        bool IsEventTypeEnabled(uint32_t type) const;

        // 事件轮询
        void PollEvents();
        void SetEnabled(bool enabled);
        bool IsEnabled() const;

        // 事件模拟
        void PushEvent(const SDL_Event& event);

        // 辅助
        SDL_Event GetLastEvent() const;

        EventManager(const EventManager&) = delete;
        EventManager& operator=(const EventManager&) = delete;

        static EventManager* Instance()
        {
            if (instance_ == nullptr)
            {
                instance_ = new EventManager;
            }
            return instance_;
        }

    private:
        EventManager() = default;
        ~EventManager() = default;

        static EventManager* instance_;

        // 内部分发函数
        void DispatchMouseMotion(const SDL_MouseMotionEvent& event);
        void DispatchMouseButton(const SDL_MouseButtonEvent& event);
        void DispatchMouseWheel(const SDL_MouseWheelEvent& event);
        void DispatchKeyboard(const SDL_KeyboardEvent& event);
        void DispatchTextInput(const SDL_TextInputEvent& event);
        void DispatchTextEditing(const SDL_TextEditingEvent& event);
        void DispatchGamepadDevice(const SDL_GamepadDeviceEvent& event);
        void DispatchGamepadButton(const SDL_GamepadButtonEvent& event);
        void DispatchGamepadAxis(const SDL_GamepadAxisEvent& event);
        void DispatchWindow(const SDL_WindowEvent& event);
        void DispatchQuit(const SDL_QuitEvent& event);

        // 统一分发
        void DispatchEvent(const SDL_Event& ev);

        // 坐标转换
        void ConvertToRenderCoords(float& x, float& y) const;
        void ConvertEventCoordinates(SDL_Event& ev);

        // 成员变量
        SDL_Window* window_ = nullptr;
        SDL_Renderer* renderer_ = nullptr;
        bool          enabled_ = true;
        bool          imgui_enabled_ = false;
        bool          block_on_imgui_capture_ = false;

        SDL_Event last_event_;

        std::vector<MouseMotionCallback>   mouse_motion_callbacks_;
        std::vector<MouseButtonCallback>   mouse_button_callbacks_;
        std::vector<MouseWheelCallback>    mouse_wheel_callbacks_;
        std::vector<KeyboardCallback>      keyboard_callbacks_;
        std::vector<TextInputCallback>     text_input_callbacks_;
        std::vector<TextEditingCallback>   text_editing_callbacks_;
        std::vector<GamepadDeviceCallback> gamepad_device_callbacks_;
        std::vector<GamepadButtonCallback> gamepad_button_callbacks_;
        std::vector<GamepadAxisCallback>   gamepad_axis_callbacks_;
        std::vector<WindowCallback>        window_callbacks_;
        std::vector<QuitCallback>          quit_callbacks_;

        std::unordered_map<uint32_t, bool> event_type_enabled_;
        std::vector<SDL_Event> pending_events_;
    };
}