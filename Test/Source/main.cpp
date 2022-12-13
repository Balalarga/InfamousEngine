#include <iostream>

#include "FileSystem/FileSystem.h"

#include "UnknownEngine/Engine.h"

using namespace Unk;

int main(int, char**)
{
    std::cout << "Hello world\n";

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
