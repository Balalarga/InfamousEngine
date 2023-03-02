#include <filesystem>

#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"
#include "Logger/Logger.h"
#include "OpenglWrap/Buffers/Buffer.h"
#include "InfamousEngine/Components/RenderComponent.h"
#include "OpenglWrap/Shaders/Resources/ShaderProgramResource.h"
#include "OpenglWrap/Texture/TextureResource.h"
#include "ResourceManager/ResourceManager.h"
#include "WindowSystem/Input/InputManager.h"
#include "WindowSystem/Windows/GameWindow.h"



class Object
{
public:
    std::shared_ptr<Inf::RenderComponent> render;
};

int main(int argc, char** argv)
{
    using namespace Inf;

    CommandArgsStorage::ParseArgValues(argc, argv);
    ResourceManager::SetResourceDir(RESOURCES_DIR);

    Engine& engine = Engine::Self();

    // Server window
    // engine.CreateWindow<ServerInvisibleWindow>();

    engine.Init();

    auto& window = dynamic_cast<Engine::DefaultWindowType&>(engine.GetWindow());

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

    struct Vertex
    {
        glm::vec3 pos;
        glm::vec4 color;
    };
    std::vector<Vertex> vertices
    {
        {{-0.5, -0.5, 0}, {1, 1, 1, 1}},
        {{-0.5,  0.5, 0}, {1, 1, 1, 1}},
        {{ 0.5,  0.5, 0}, {1, 1, 1, 1}},
        {{ 0.5, -0.5, 0}, {1, 1, 1, 1}}
    };

    Buffer buffer(DataPtr(vertices), BufferLayout().Float(3).Float(4));
    buffer.DrawType = GL_QUADS;

    // TODO: Compile-time reflection system
    Object obj;
    obj.render = std::make_shared<RenderComponent>();
    // Cannot render any of RenderableComponent's children types, because of typeid miss match while ReadAllComponentsOf
    buffer.Create();
    obj.render->SetBuffer(buffer);
    obj.render->SetShaderProgram(program->Take());

    Logger::Log("Entity created");

    engine.Run();

    return 0;
}
