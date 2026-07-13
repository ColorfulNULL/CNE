#include "EventManager.hpp"

cne::EventManager* cne::EventManager::instance_ = nullptr;

void cne::EventManager::Init()
{
    window_ = WindowManager::Instance()->window_;
    renderer_ = RendererManager::Instance()->renderer_;
    enabled_ = true;
    imgui_enabled_ = false;
    block_on_imgui_capture_ = false;
    SDL_zero(last_event_);
}

void cne::EventManager::RegisterMouseMotion(MouseMotionCallback cb)
{
    mouse_motion_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterMouseButton(MouseButtonCallback cb)
{
    mouse_button_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterMouseWheel(MouseWheelCallback cb)
{
    mouse_wheel_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterKeyboard(KeyboardCallback cb)
{
    keyboard_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterTextInput(TextInputCallback cb)
{
    text_input_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterTextEditing(TextEditingCallback cb)
{
    text_editing_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterGamepadDevice(GamepadDeviceCallback cb)
{
    gamepad_device_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterGamepadButton(GamepadButtonCallback cb)
{
    gamepad_button_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterGamepadAxis(GamepadAxisCallback cb)
{
    gamepad_axis_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterWindow(WindowCallback cb)
{
    window_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::RegisterQuit(QuitCallback cb)
{
    quit_callbacks_.push_back(std::move(cb));
}

void cne::EventManager::ClearCallbacks()
{
    mouse_motion_callbacks_.clear();
    mouse_button_callbacks_.clear();
    mouse_wheel_callbacks_.clear();
    keyboard_callbacks_.clear();
    text_input_callbacks_.clear();
    text_editing_callbacks_.clear();
    gamepad_device_callbacks_.clear();
    gamepad_button_callbacks_.clear();
    gamepad_axis_callbacks_.clear();
    window_callbacks_.clear();
    quit_callbacks_.clear();
}

// ImGui 控制
void cne::EventManager::SetImGuiHandlingEnabled(bool enabled)
{
    imgui_enabled_ = enabled;
}

void cne::EventManager::SetBlockOnImGuiCapture(bool block)
{
    block_on_imgui_capture_ = block;
}

// 事件类型启用
void cne::EventManager::SetEventTypeEnabled(uint32_t type, bool enabled)
{
    event_type_enabled_[type] = enabled;
}

bool cne::EventManager::IsEventTypeEnabled(uint32_t type) const
{
    auto it = event_type_enabled_.find(type);
    return it != event_type_enabled_.end() ? it->second : true;
}

// 全局启用
void cne::EventManager::SetEnabled(bool enabled)
{
    enabled_ = enabled;
}

bool cne::EventManager::IsEnabled() const
{
    return enabled_;
}

// 辅助
SDL_Event cne::EventManager::GetLastEvent() const
{
    return last_event_;
}

void cne::EventManager::PushEvent(const SDL_Event& event)
{
    pending_events_.push_back(event);
}

// 坐标转换
void cne::EventManager::ConvertToRenderCoords(float& x, float& y) const
{
    if (renderer_)
    {
        SDL_RenderCoordinatesFromWindow(renderer_, x, y, &x, &y);
    }
}

void cne::EventManager::ConvertEventCoordinates(SDL_Event& ev)
{
    switch (ev.type)
    {
    case SDL_EVENT_MOUSE_MOTION:
    {
        float x = static_cast<float>(ev.motion.x);
        float y = static_cast<float>(ev.motion.y);
        ConvertToRenderCoords(x, y);
        ev.motion.x = static_cast<int>(x);
        ev.motion.y = static_cast<int>(y);
        break;
    }
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
    {
        float x = static_cast<float>(ev.button.x);
        float y = static_cast<float>(ev.button.y);
        ConvertToRenderCoords(x, y);
        ev.button.x = static_cast<int>(x);
        ev.button.y = static_cast<int>(y);
        break;
    }
    default:
        break;
    }
}

// 内部分发
void cne::EventManager::DispatchMouseMotion(const SDL_MouseMotionEvent& event)
{
    for (const auto& cb : mouse_motion_callbacks_) cb(event);
}

void cne::EventManager::DispatchMouseButton(const SDL_MouseButtonEvent& event)
{
    for (const auto& cb : mouse_button_callbacks_) cb(event);
}

void cne::EventManager::DispatchMouseWheel(const SDL_MouseWheelEvent& event)
{
    for (const auto& cb : mouse_wheel_callbacks_) cb(event);
}

void cne::EventManager::DispatchKeyboard(const SDL_KeyboardEvent& event)
{
    for (const auto& cb : keyboard_callbacks_) cb(event);
}

void cne::EventManager::DispatchTextInput(const SDL_TextInputEvent& event)
{
    for (const auto& cb : text_input_callbacks_) cb(event);
}

void cne::EventManager::DispatchTextEditing(const SDL_TextEditingEvent& event)
{
    for (const auto& cb : text_editing_callbacks_) cb(event);
}

void cne::EventManager::DispatchGamepadDevice(const SDL_GamepadDeviceEvent& event)
{
    for (const auto& cb : gamepad_device_callbacks_) cb(event);
}

void cne::EventManager::DispatchGamepadButton(const SDL_GamepadButtonEvent& event)
{
    for (const auto& cb : gamepad_button_callbacks_) cb(event);
}

void cne::EventManager::DispatchGamepadAxis(const SDL_GamepadAxisEvent& event)
{
    for (const auto& cb : gamepad_axis_callbacks_) cb(event);
}

void cne::EventManager::DispatchWindow(const SDL_WindowEvent& event)
{
    for (const auto& cb : window_callbacks_) cb(event);
}

void cne::EventManager::DispatchQuit(const SDL_QuitEvent& event)
{
    for (const auto& cb : quit_callbacks_) cb(event);
}

void cne::EventManager::DispatchEvent(const SDL_Event& ev)
{
    if (!IsEventTypeEnabled(ev.type)) return;

    switch (ev.type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        DispatchMouseMotion(ev.motion);
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
    case SDL_EVENT_MOUSE_BUTTON_UP:
        DispatchMouseButton(ev.button);
        break;
    case SDL_EVENT_MOUSE_WHEEL:
        DispatchMouseWheel(ev.wheel);
        break;
    case SDL_EVENT_KEY_DOWN:
    case SDL_EVENT_KEY_UP:
        DispatchKeyboard(ev.key);
        break;
    case SDL_EVENT_TEXT_INPUT:
        DispatchTextInput(ev.text);
        break;
    case SDL_EVENT_TEXT_EDITING:
        DispatchTextEditing(ev.edit);
        break;
    case SDL_EVENT_GAMEPAD_ADDED:
    case SDL_EVENT_GAMEPAD_REMOVED:
    case SDL_EVENT_GAMEPAD_REMAPPED:
        DispatchGamepadDevice(ev.gdevice);
        break;
    case SDL_EVENT_GAMEPAD_BUTTON_DOWN:
    case SDL_EVENT_GAMEPAD_BUTTON_UP:
        DispatchGamepadButton(ev.gbutton);
        break;
    case SDL_EVENT_GAMEPAD_AXIS_MOTION:
        DispatchGamepadAxis(ev.gaxis);
        break;
    case SDL_EVENT_WINDOW_RESIZED:
    case SDL_EVENT_WINDOW_CLOSE_REQUESTED:
    case SDL_EVENT_WINDOW_FOCUS_GAINED:
    case SDL_EVENT_WINDOW_FOCUS_LOST:
        DispatchWindow(ev.window);
        break;
    case SDL_EVENT_QUIT:
        DispatchQuit(ev.quit);
        break;
    default:
        break;
    }
}

void cne::EventManager::PollEvents()
{
    if (!enabled_) return;

    // 处理模拟事件
    for (auto& ev : pending_events_)
    {
        ConvertEventCoordinates(ev);
        DispatchEvent(ev);
    }
    pending_events_.clear();

    // 轮询真实事件
    SDL_Event ev;
    while (SDL_PollEvent(&ev))
    {
        last_event_ = ev;
        ConvertEventCoordinates(ev);

        bool imguiProcessed = false;
        if (imgui_enabled_)
        {
            imguiProcessed = ImGui_ImplSDL3_ProcessEvent(&ev) != 0;
        }
        if (imguiProcessed && block_on_imgui_capture_)
        {
            continue;
        }
        DispatchEvent(ev);
    }
}