#pragma once
#include <string>

class Resource
{
public:
	Resource(std::string resourcePath);

private:
	const std::string _resourcePath;
	const size_t _hash;
};
