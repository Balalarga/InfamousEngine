#include <filesystem>

#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"

#include "Logger/Logger.h"
#include "OpenglWrap/Shaders/ShaderProgram.h"

#include "OpenglWrap/Shaders/Resources/ShaderResource.h"

#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/Resources/JsonResource.h"


int main(int argc, char** argv)
{
    using namespace Inf;

    CommandArgsStorage::ParseArgValues(argc, argv);
    ResourceManager::SetResourceDir(RESOURCES_DIR);

    Engine& engine = Engine::Self();
    engine.Init();

    engine.GetWindow().Resize(768,432);

    engine.GetInputManager().Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
    {
        if (state == KeyState::Pressed)
            Engine::Self().RequestClosing();
    });

    const std::shared_ptr<ShaderResource> vert = ResourceManager::LoadResource<ShaderResource>("Shaders/default.vsh");
    const std::shared_ptr<ShaderResource> frag = ResourceManager::LoadResource<ShaderResource>("Shaders/default.fsh");
    std::shared_ptr<ShaderProgram> prog;
    if (!vert || !frag)
    {
        Logger::Error("Couldn't load shader");
    }
    else
    {
        prog = std::make_shared<ShaderProgram>(vert->Take(), frag->Take());
        if (!prog->Compile())
            Logger::Error("Couldn't compile ShaderProgram");
        else
            Logger::Log("ShaderProgram compiled");
    }

    engine.Run();

    return 0;
}
