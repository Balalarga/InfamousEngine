#include <filesystem>

#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"

#include "Logger/Logger.h"

#include "OpenglWrap/Shaders/ShaderResource.h"

#include "ResourceManager/Resources/JsonResource.h"

using namespace Inf;

int main(int argc, char** argv)
{
    CommandArgsStorage::ParseArgValues(argc, argv);
    Engine::SetResourceDir(RESOURCES_DIR);

    Engine& engine = Engine::Self();
    engine.Init();

    ResourceManager& resourceManager = engine.GetResourceManager();
    const std::shared_ptr resources = resourceManager.LoadResource<ShaderResource>("Shaders/default.vsh");
    if (!resources)
        Logger::Error("Couldn't load shader");

    if (!(**resources).Compile())
        Logger::Error("Couldn't compile shader");

    engine.GetInputManager().Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
    {
        if (state == KeyState::Pressed)
            Engine::Self().RequestClosing();
    });

    engine.Run();

    return 0;
}
