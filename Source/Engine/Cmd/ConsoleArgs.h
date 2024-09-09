#pragma once


class ConsoleArgs
{
public:
	static ConsoleArgs& Get();
	static void Init(int argc, char** argv);


private:
	ConsoleArgs() = default;

	int _argc = 0;
	char** _argv = nullptr;
};