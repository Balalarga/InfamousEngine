#include "CommandArgsStorage.h"

#include <sstream>

#include "Logger/Logger.h"

namespace Inf
{
std::map<std::string, CommandArgsStorage::ArgValue> CommandArgsStorage::sArguments;

void CommandArgsStorage::ParseArgValues(int argc, char** argv)
{
	std::stringstream stream;

	for (int i = 0; i < argc; ++i)
		stream << argv[i] << (i != argc-1 ? ", " : "");
	Logger::Log(stream.str());
}

CommandArgsStorage::ArgValue* CommandArgsStorage::Find(const std::string& arg)
{
	const auto it = sArguments.find(arg);
	if (it != sArguments.end())
		return &it->second;

	return nullptr;
}

bool CommandArgsStorage::Contains(const std::string& arg)
{
	return Find(arg) != nullptr;
}
}
