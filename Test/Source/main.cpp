#include <filesystem>

#include "ECS/ECSStorage.h"
#include "ECS/Entity.h"
#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Components/MeshComponent.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"

#include "Logger/Logger.h"
#include "OpenglWrap/Shaders/Resources/ShaderProgramResource.h"
#include "OpenglWrap/Texture/TextureResource.h"

#include "ResourceManager/ResourceManager.h"
#include "ResourceManager/Resources/JsonResource.h"
#include "WindowSystem/Input/InputManager.h"
#include "WindowSystem/Windows/ServerInvisibleWindow.h"


int main(int argc, char** argv)
{
    using namespace Inf;

    CommandArgsStorage::ParseArgValues(argc, argv);
    ResourceManager::SetResourceDir(RESOURCES_DIR);

    Engine& engine = Engine::Self();

    // Server window
    // engine.CreateWindow<ServerInvisibleWindow>();

    engine.Init();

    IWindow& window = engine.GetWindow();

    engine.GetWindow().Resize(768,432);

    if (window.GetInputManager())
    {
        window.GetInputManager()->Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
        {
            if (state == KeyState::Pressed)
                Engine::Self().RequestClosing();
        });
    }

    std::shared_ptr program = ResourceManager::LoadResource<ShaderProgramResource>("shaderProgram.json");
    if (!program)
        Logger::Error("Couldn't load shader");

    std::shared_ptr image = ResourceManager::LoadResource<TextureResource>("Images/blueprint.png");
    if (!image)
        Logger::Error("Couldn't load image");

    std::shared_ptr<Entity> ent = ECSStorage::Create<Entity>();
    ent->AddComponent<MeshComponent>("Mesh");
    Logger::Log("Entity created");


    engine.Run();

    return 0;
}
