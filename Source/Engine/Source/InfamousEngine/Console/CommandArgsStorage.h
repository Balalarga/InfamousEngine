#pragma once
#include <string>
#include <variant>
#include <map>

namespace Inf
{

class CommandArgsStorage
{
public:
	using ArgValue = std::variant<int, float, double, std::string>;

	CommandArgsStorage() = delete;
	CommandArgsStorage(CommandArgsStorage&&) = delete;
	CommandArgsStorage(const CommandArgsStorage&) = delete;
	~CommandArgsStorage() = delete;

	static void ParseArgValues(int argc, char** argv);

	static bool Contains(const std::string& arg);

	static ArgValue* Find(const std::string& arg);

	template<class T> // TODO
	static T* Find(const std::string& arg)
	{
		ArgValue* val = Find(arg);
		if (!val)
			return nullptr;
		return nullptr;
	}

private:
	static std::map<std::string, ArgValue> sArguments;

};
}
