#include "Cmd/ConsoleArgs.h"
#include "Engine/Engine.h"


int main(int argc, char** argv)
{
	ConsoleArgs::Init(argc, argv);

	Engine engine;

	engine.Start();

	return 0;
}