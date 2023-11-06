#include <iostream>
#include "Engine.h"
#include "IWindowUpdateLoop.h"
#include "Impl/Window.h"
#include "Json.h"

using namespace Inf;

int main(int argc, char** argv)
{
	WindowParams params;
	Window window;
	auto loop = std::make_unique<SimpleWindowUpdateLoop>();
	loop->SetFrameLimit(60);
	window.Run(std::move(loop));
	return 0;
}
