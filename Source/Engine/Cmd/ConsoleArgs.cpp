#include "ConsoleArgs.h"


ConsoleArgs& ConsoleArgs::Get()
{
	static ConsoleArgs self;
	return self;
}

void ConsoleArgs::Init(int argc, char** argv)
{
	auto& self = Get();
	self._argc = argc;
	self._argv = argv;
}