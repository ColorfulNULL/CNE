#pragma once

#pragma execution_character_set("utf-8")

// 第三方库
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <imgui.h>
#include <imgui_internal.h>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>
#include <box2d/box2d.h>
#include <cereal/archives/json.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/string.hpp>
#include <nlohmann/json.hpp>
#include <entt/entt.hpp>

// 标准库
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <map>
#include <chrono>
#include <random>
#include <functional>
#include <algorithm>
#include <stdexcept>
#include <cmath>
#include <deque>
#include <thread>
#include <unordered_map>

using Json = nlohmann::json;