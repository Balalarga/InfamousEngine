#include <iostream>

#include "FileSystem/FileSystem.h"

#include "UnknownEngine/Engine.h"

using namespace Unk;

int main(int argc, char** argv)
{
    std::cout << "Hello world\n";

    Engine& engine = Engine::Self();
    engine.CreateWindow<GameWindow>();

    engine.Run();

    return 0;
}
