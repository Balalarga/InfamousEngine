#include <iostream>

#include "FileSystem/FileSystem.h"

#include "InfamousEngine/Engine.h"

using namespace Inf;

int main(int, char**)
{
    Engine& engine = Engine::Self();
    engine.CreateWindow<GameWindow>();

    engine.GetInputManager().Add(SDL_SCANCODE_ESCAPE, [](const KeyState& state)
    {
        if (state == KeyState::Pressed)
            Engine::Self().RequestClosing();
    });

    engine.Run();

    return 0;
}
