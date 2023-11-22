#include <iostream>
#include "Engine.h"
#include "Impl/Window.h"
#include "Json.h"

using namespace Inf;

int main(int argc, char** argv)
{
	WindowParams params;
	params.fps = 60;
	Window window(std::move(params));
	window.Run();
	return 0;
}
