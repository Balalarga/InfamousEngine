#pragma once
#include <map>
#include <set>
#include <string>

#include "ResourceHandler.h"


namespace Inf
{
class Resource;

class ResourceManager
{
public:
	ResourceManager() = default;
	virtual ~ResourceManager() = default;

	ResourceHandler* FindTypeHandler(const std::string& type);

	bool AddTypeHandler(const std::string& type, ResourceHandler&& func);
	bool AddTypeHandlers(const std::vector<std::string>& types, ResourceHandler&& handler);

	bool ResetTypeHandler(const std::string& type, ResourceHandler&& func);

	std::shared_ptr<Resource> LoadResource(const std::string& filepath);

	std::shared_ptr<Resource> FindResource(const std::string& filepath);
	std::shared_ptr<Resource> FindResource(size_t hash);

protected:
	std::map<std::string, ResourceHandler> _resourceHandlers;
	std::map<size_t, std::shared_ptr<Resource>> _resources;
};
}

