#pragma once
#include <filesystem>


class Config
{
public:
	explicit Config(std::filesystem::path path);
	const std::filesystem::path& GetPath() const;


private:
	std::filesystem::path _path;
};
