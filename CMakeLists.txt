# 设定最低CMake版本
cmake_minimum_required(VERSION 3.20)
 
# 项目预设
project(SuperBouncyBall LANGUAGES C CXX VERSION 1.0.0)

# C/C++标准
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
 
# /MT
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

# 强制静态库
set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE)
set(SDL_SHARED_ENABLED_BY_DEFAULT OFF CACHE BOOL "" FORCE)
set(SDL_STATIC_ENABLED_BY_DEFAULT ON CACHE BOOL "" FORCE)
set(SDL_TEST OFF CACHE BOOL "" FORCE)

# 输出目录
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 兼容性
set(SDLIMAGE_AVIF OFF CACHE BOOL "Disable AVIF support" FORCE)

# 导入第三方库
add_subdirectory(src/external/SDL3)
add_subdirectory(src/external/SDL3_image)
add_subdirectory(src/external/SDL3_ttf)
add_subdirectory(src/external/SDL3_mixer)
add_subdirectory(src/external/box2d)
add_subdirectory(src/external/nlohmann_json)
add_subdirectory(src/external/entt)

# 收集项目源码
file(GLOB_RECURSE PROJECT_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CNE/*.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/src/CNE/*.cpp"
)

# 收集ImGUI源码
list(APPEND PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

# 收集Box2D源码
file(GLOB_RECURSE BOX2D_SOURCES 
    "${CMAKE_CURRENT_SOURCE_DIR}/src/external/box2d/src/*.c"
)
list(APPEND PROJECT_SOURCES ${BOX2D_SOURCES})

# 收集ImGUI源码
list(APPEND PROJECT_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/imgui.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/imgui_draw.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/imgui_tables.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/imgui_widgets.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/imgui_demo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/backends/imgui_impl_sdl3.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui/backends/imgui_impl_sdlrenderer3.cpp
)

# 可执行文件
add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})

# 包含头文件路径
target_include_directories(${PROJECT_NAME} PRIVATE
    ${SDL3_SOURCE_DIR}/include
    ${SDL_IMAGE_SOURCE_DIR}/include
    ${SDL_MIXER_SOURCE_DIR}/include
    ${SDL_TTF_SOURCE_DIR}/include
    ${box2d_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/imgui
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/cereal/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/nlohmann_json/include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/external/entt/single_include
    ${CMAKE_CURRENT_SOURCE_DIR}/src/CNE
)

# 链接静态库
target_link_libraries(${PROJECT_NAME} PRIVATE
    SDL3::SDL3
    SDL3_image::SDL3_image
    SDL3_mixer::SDL3_mixer
    SDL3_ttf::SDL3_ttf
)