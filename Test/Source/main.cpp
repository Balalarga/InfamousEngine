#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"
#include "ResourceManager/Resources/JsonResource.h"

using namespace Inf;

int main(int argc, char** argv)
{
    CommandArgsStorage::ParseArgValues(argc, argv);

    Engine& engine = Engine::Self();
    engine.Init();

    ResourceManager& resourceManager = engine.GetResourceManager();
    resourceManager.LoadResource<JsonResource>(R"(C:\UnrealEngines\R3-4.26.2-source\Engine\Programs\UnrealInsights\Saved\R3PerfResults.json)");

    engine.GetInputManager().Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
    {
        if (state == KeyState::Pressed)
            Engine::Self().RequestClosing();
    });


    engine.Run();

    return 0;
}
