#include <iostream>

#include "InfamousEngine/Engine.h"
#include "InfamousEngine/Console/CommandArgsStorage.h"

using namespace Inf;

int main(int argc, char** argv)
{
    CommandArgsStorage::ParseArgValues(argc, argv);

    Engine& engine = Engine::Self();
    engine.Init();

    engine.GetInputManager().Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
    {
        if (state == KeyState::Pressed)
            Engine::Self().RequestClosing();
    });

    engine.Run();

    return 0;
}
