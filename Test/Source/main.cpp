#include <filesystem>

#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"

#include "Logger/Logger.h"

#include "OpenglWrap/Shaders/ShaderResource.h"

#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/Resources/JsonResource.h"

using namespace Inf;

template<class T = void>
void LoadResource()
{
    assert(false);
}

template<>
void LoadResource<float>()
{
    Logger::Log("overload");
}

int main(int argc, char** argv)
{
    CommandArgsStorage::ParseArgValues(argc, argv);
    ResourceManager::SetResourceDir(RESOURCES_DIR);

    Engine& engine = Engine::Self();
    engine.Init();

    const std::shared_ptr resources = ResourceManager::LoadResource<ShaderResource>("Shaders/default.vsh");
    if (!resources)
    {
        Logger::Error("Couldn't load shader");
    }
    else
    {
        if (!(**resources).Compile())
            Logger::Error("Couldn't compile shader");
        else
            Logger::Error("Shader compiled");
    }

    engine.GetInputManager().Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
    {
        if (state == KeyState::Pressed)
            Engine::Self().RequestClosing();
    });

    engine.Run();

    return 0;
}
