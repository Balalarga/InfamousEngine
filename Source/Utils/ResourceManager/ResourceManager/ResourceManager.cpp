#include "ResourceManager.h"

#include <memory>
#include <stdexcept>

namespace Inf
{
static std::unique_ptr<ResourceManager> _sInstance;

ResourceManager& ResourceManager::Setup(Settings settings)
{
	if (!_sInstance)
		throw std::runtime_error("ResourceManager::Setup is called after an ResourceManager has already been created");

	_sInstance = std::make_unique<ResourceManager>(std::move(settings));
	return *_sInstance;
}

ResourceManager& ResourceManager::Instance()
{
	if (!_sInstance)
		_sInstance = std::make_unique<ResourceManager>();

	return *_sInstance;
}

ResourceManager::ResourceManager(Settings settings):
	_settings(std::move(settings))
{
}

}
