#include <iostream>

#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"
#include "Logger/Logger.h"

using namespace Inf;

std::shared_ptr<Resource> TxtHandler(const std::string& filepath)
{
    Logger::Log("Text resource loading");
    return nullptr;
}

int main(int argc, char** argv)
{
    CommandArgsStorage::ParseArgValues(argc, argv);

    Engine& engine = Engine::Self();
    engine.Init();
    ResourceManager& resourceManager = engine.GetResourceManager();

    engine.GetInputManager().Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
    {
        if (state == KeyState::Pressed)
            Engine::Self().RequestClosing();
    });

    engine.Run();

    return 0;
}
