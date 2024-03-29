#include "Engine.h"

#include "Coordinator.h"
#include "Systems/CameraSystem.h"
#include "Systems/CollisionSystem.h"
#include "Systems/LogSystem.h"
#include "Systems/PhysicsSystem.h"
#include "Systems/RenderSystem.h"
#include "Systems/ResourceSystem.h"
#include "Systems/TranslateSystem.h"
#include "Systems/WindowSystem.h"

#include "Components/Collider.h"
#include "Components/Mesh.h"
#include "Components/Rigidbody.h"
#include "Components/Shader.h"
#include "Components/Texture.h"
#include "Components/Transform.h"

Coordinator gCoordinator;

void Engine::Init(bool editorMode)
{
    LOG_INFO("Initializing engine...");

    gCoordinator.Init();

    // 注意下方的初始化顺序不能随意调换！（因为存在依赖关系）

    gCoordinator.RegisterComponent<Camera>();
    gCoordinator.RegisterComponent<Mesh>();
    gCoordinator.RegisterComponent<Shader>();
    gCoordinator.RegisterComponent<Texture>();
    gCoordinator.RegisterComponent<Transform>();
    gCoordinator.RegisterComponent<Rigidbody>();
    gCoordinator.RegisterComponent<Collider>();

    gCoordinator.RegisterSystem<WindowSystem>()->Init(editorMode);
    gCoordinator.RegisterSystem<RenderSystem>()->Init(editorMode);
    gCoordinator.RegisterSystem<ResourceSystem>()->Init(editorMode);
    gCoordinator.RegisterSystem<TranslateSystem>()->Init(editorMode);
    gCoordinator.RegisterSystem<PhysicsSystem>()->Init(editorMode);
    gCoordinator.RegisterSystem<CollisionSystem>()->Init(editorMode);
    gCoordinator.RegisterSystem<CameraSystem>()->Init(editorMode);

    if (!editorMode)
        gCoordinator.GetSystem<ResourceSystem>()->LoadResource();
}

void Engine::Run()
{
    LOG_INFO("Running engine...");

    auto windowSystem = gCoordinator.GetSystem<WindowSystem>();
    auto renderSystem = gCoordinator.GetSystem<RenderSystem>();

    while (!windowSystem->WindowShouldClose())
    {
        renderSystem->BeginFrame();

        Tick(windowSystem->CountDeltaTime());

        renderSystem->Render();
        renderSystem->EndFrame();

        windowSystem->EndFrame();
    }
}

void Engine::RunEx(const std::function<void()> &func)
{
    auto windowSystem = gCoordinator.GetSystem<WindowSystem>();
    auto renderSystem = gCoordinator.GetSystem<RenderSystem>();

    while (!windowSystem->WindowShouldClose())
    {
        renderSystem->BeginFrame();

        Tick(windowSystem->CountDeltaTime());

        renderSystem->Render();
        renderSystem->EndFrame();

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

void Engine::Tick(float dt)
{
    gCoordinator.UpdateSystems(dt);
}
