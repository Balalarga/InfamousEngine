#include "Config.h"

Config::Config(std::filesystem::path path):
	_path(std::move(path))
{

}

const std::filesystem::path& Config::GetPath() const
{
	return _path;
}
