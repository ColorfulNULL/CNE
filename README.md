# CNE
Chroma Null Engine是一个SDL3+Box2D+ImGUI的开发框架

◆ 许可证：MIT（详见 LICENSE 文件）
◆ 依赖库：SDL3 · Box2D · ImGui · nlohmann/json · cereal
◆ 语言标准：C++17


◆ 概述 ◆
──────────
ChromaNullEngine 是一款轻量级但功能丰富的 C++ 游戏框架，为您构建 2D 游戏或交互式应用提供一切所需。它封装了底层 SDL3 细节，同时提供了资产管理、事件处理、场景管理、2D 物理（Box2D）和即时模式 GUI（ImGui）等强大系统。代码风格简洁、易于扩展，遵循现代 C++17 规范。


◆ 核心特性 ◆
──────────────

◈ 基础系统
  ▶ 窗口与渲染器管理 – 轻松创建和控制窗口，支持全屏、无边框、透明度、窗口形状等功能，逻辑分辨率缩放确保渲染一致。
  ▶ 事件系统 – 为鼠标、键盘、手柄、窗口和退出事件注册回调，内置 ImGui 集成，可阻止 GUI 捕获的事件继续下发。
  ▶ 场景管理 – 提供 Scene 基类（Init/Update/Render/HandleEvent/Quit），场景切换零负担。

◈ 资产管线
  ▶ 纹理、字体、音频、文本资源池 – 一行代码加载图片、TrueType 字体、音频，支持按名称查询、获取和释放。
  ▶ 文本表 – 加载 JSON 格式的字符串表，轻松实现本地化。
  ▶ 动态文本渲染 – 使用已加载字体将任意字符串实时生成为纹理，支持自定义大小和颜色。

◈ 2D 相机与视口
  ▶ 平滑跟随 – 跟踪 Box2D 刚体或世界坐标，平滑速度可调。
  ▶ 死区 – 定义相机不移动的区域，减少抖动。
  ▶ 边界钳制 – 将相机限制在世界边界内。
  ▶ 震动效果 – 随机或正弦波相机震动。
  ▶ 缩放平滑过渡 – 独立控制缩放平滑度。
  ▶ 坐标转换 – 世界坐标 ↔ 屏幕坐标 互转。

◈ 音频
  ▶ 混音器抽象 – 播放、暂停、恢复、停止、跳转，支持淡入淡出。
  ▶ 音量控制 – 全局或独立音轨音量。
  ▶ 预解码 – 可选预解码以降低延迟（牺牲内存）。

◈ 物理（Box2D）
  ▶ 无缝集成 – 框架不封装 Box2D，Camera 类直接使用 b2BodyId 和 b2Vec2，让物理与渲染结合非常简单。

◈ ImGui 集成
  ▶ 可开关 GUI – 运行时启用/禁用 ImGui 事件处理。
  ▶ 捕获时阻断 – 当 ImGui 捕获事件时，阻止游戏事件继续分发（适合编辑器工具）。

◈ 性能与工具
  ▶ FPS 限制器 – 设置最大帧率并实时获取当前 FPS。
  ▶ 定时器 – 支持回调、暂停/恢复。
  ▶ 随机数生成器 – 线程局部单例，提供均匀、正态、布尔分布。
  ▶ 2D 向量数学 – 全面的 Vector2D 类（旋转、投影、反射、插值等）。

◈ 序列化
  ▶ JSON（nlohmann/json）– 轻松读写结构化数据。
  ▶ 二进制（cereal）– 快速紧凑的二进制序列化，适用于存档或自定义数据。


◆ 依赖库 ◆
────────────
  • SDL3          – 跨平台多媒体库
  • SDL3_image    – 图片加载
  • SDL3_ttf      – TrueType 字体
  • SDL3_mixer    – 音频混音
  • Box2D         – 2D 物理引擎
  • Dear ImGui    – 即时模式 GUI
  • nlohmann/json – 现代 C++ JSON 库
  • cereal        – C++11 序列化库

注意：需自行安装并链接这些库。


◆ 目录结构 ◆
──────────────
ChromaNullEngine/
├─ Core/                    # 核心管理器（单例）
│  ├─ SDLManager            # SDL 初始化/退出
│  ├─ WindowManager         # 窗口创建与属性
│  ├─ RendererManager       # 渲染（逻辑分辨率、渲染目标）
│  ├─ MixerManager          # 音频设备与音轨控制
│  ├─ AssetManager          # 纹理、字体、音频、文本池
│  ├─ EventManager          # 事件分发（支持 ImGui）
│  ├─ FileManager           # JSON/二进制序列化
│  ├─ FPSManager            # 帧率限制与 FPS 计数
│  ├─ AnimationManager      # 帧动画存储
│  └─ SceneManager          # 场景切换与生命周期
├─ Model/                   # 数据结构
│  ├─ Asset/                # Image, Font, Audio, Text
│  ├─ Tile/                 # 动画帧定义
│  ├─ Animation/            # 动画（Tile 列表）
│  └─ Scene/                # Scene 抽象基类
├─ Utility/                 # 工具类
│  ├─ Camera/               # 2D 相机（跟随、震动、缩放）
│  ├─ Random/               # 随机数生成器
│  ├─ Timer/                # 定时回调
│  └─ Vector2D/             # 向量数学工具
└─ external.hpp             # 公共头文件包含


◆ 快速开始 ◆
──────────────

► 前置条件
  • C++17 编译器（MSVC、GCC、Clang）
  • CMake 3.12+
  • 安装上述依赖库

► 集成到您的项目
  将引擎源码复制到您的工程，在 CMake 中添加子目录并链接依赖库。

  最小 CMakeLists.txt 示例：
  ════════════════════════════════════════════════════════════
  cmake_minimum_required(VERSION 3.12)
  project(MyGame)
  set(CMAKE_CXX_STANDARD 17)

  add_subdirectory(ChromaNullEngine)

  add_executable(MyGame main.cpp)
  target_link_libraries(MyGame
      ChromaNullEngine
      SDL3::SDL3
      SDL3_image::SDL3_image
      SDL3_ttf::SDL3_ttf
      SDL3_mixer::SDL3_mixer
      box2d
      imgui
      nlohmann_json
      cereal
  )
  ════════════════════════════════════════════════════════════

► 基本使用示例
  ════════════════════════════════════════════════════════════
  #include "Core/Core.hpp"

  class MyScene : public cne::Scene {
  public:
      void Init() override {
          cne::AssetManager::Instance()->LoadImage("assets/player.png", "player");
      }
      void Render() override {
          auto img = cne::AssetManager::Instance()->GetImage("player");
          SDL_FRect dst{100, 100, 64, 64};
          cne::RendererManager::Instance()->Render(img.texture, nullptr, &dst);
      }
  };

  int main() {
      cne::SDLManager::Instance()->Init();
      cne::WindowManager::Instance()->Init("My Game", {100, 100, 800, 600});
      cne::RendererManager::Instance()->Init(800, 600);
      cne::MixerManager::Instance()->Init();
      cne::EventManager::Instance()->Init();

      MyScene scene;
      cne::SceneManager::Instance()->Init(&scene);

      while (true) {
          cne::FPSManager::Instance()->Begin();
          cne::EventManager::Instance()->PollEvents();
          cne::SceneManager::Instance()->HandleEvent();
          cne::SceneManager::Instance()->Update();
          cne::RendererManager::Instance()->Begin();
          cne::SceneManager::Instance()->Render();
          cne::RendererManager::Instance()->End();
          cne::FPSManager::Instance()->End();
      }
      // 退出前手动调用各管理器的 Quit/Free 释放资源
      return 0;
  }
  ════════════════════════════════════════════════════════════


◆ 文档 ◆
──────────
引擎源码中包含大量中英文注释，详细说明每个类的用法。所有管理器均为单例模式，通过 ClassName::Instance() 全局访问。建议阅读各头文件获取完整接口信息。


◆ 贡献 ◆
──────────
欢迎提交 Issue 和 Pull Request！无论是修复 Bug、改进功能还是增加新特性，我们都非常感谢。请保持代码风格一致（缩进、命名等）。


◆ 许可证 ◆
────────────
ChromaNullEngine 使用 MIT 许可证。详见项目根目录下的 LICENSE 文件。

◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆◆

由 ChromaNull 社区用心打造 – 祝您游戏开发愉快！
