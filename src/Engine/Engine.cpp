#include "Engine.h"

#include "Coordinator.h"
#include "Systems/LogSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/TranslateSystem.h"
#include "Systems/WindowSystem.h"

#include <chrono>

Coordinator gCoordinator;

void Engine::Init()
{
    LOG_INFO("Initializing engine...");

    gCoordinator.Init();

    // 注意下方的初始化顺序不能随意调换！（因为存在依赖关系）

    gCoordinator.RegisterSystem<WindowSystem>();
    gCoordinator.RegisterSystem<RenderSystem>();
    gCoordinator.RegisterSystem<TranslateSystem>();
}

void Engine::Run()
{
    LOG_INFO("Running engine...");

    auto windowSystem = gCoordinator.GetSystem<WindowSystem>();

    while (!windowSystem->WindowShouldClose())
    {
        float dt = CalculateDeltaTime();
        // std::cout << "delta time: " << dt << " FPS: " << 1 / dt << std::endl;

        Tick(dt);

        windowSystem->EndFrame();
    }
}

void Engine::RunEx(const std::function<void()> &func)
{
    auto windowSystem = gCoordinator.GetSystem<WindowSystem>();

    while (!windowSystem->WindowShouldClose())
    {
        float dt = CalculateDeltaTime();
        // std::cout << "delta time: " << dt << " FPS: " << 1 / dt << std::endl;

        Tick(dt);

        func();

        windowSystem->EndFrame();
    }
}

void Engine::Shutdown()
{
    LOG_INFO("Shutting down engine...");

    // 同理，下方的销毁顺序也不能随意调换

    gCoordinator.DestorySystem<TranslateSystem>();
    gCoordinator.DestorySystem<RenderSystem>();
    gCoordinator.DestorySystem<WindowSystem>();
}

float Engine::CalculateDeltaTime()
{
    using tp = std::chrono::time_point<std::chrono::steady_clock>;
    static tp prev;
    static float deltaTime;

    tp now;

    now = std::chrono::steady_clock::now();

    // 均值滤波：防止 delta time 的骤变
    deltaTime = 0.9f * deltaTime +
                0.1f * std::chrono::duration_cast<std::chrono::microseconds>(now - prev).count() / 1000000.0f;

    prev = now;

    return deltaTime;
}

void Engine::Tick(float dt)
{
    gCoordinator.UpdateSystems(dt);
}
