#pragma once
#include <filesystem>


namespace Inf
{


class ResourceManager
{
public:
	struct Settings
	{
		std::filesystem::path rootDir;
	};


	// Should be called once, before any Instance() function calls
	// Either a exception will be thrown
	static ResourceManager& Setup(Settings settings);
	static ResourceManager& Instance();


private:
	ResourceManager(Settings settings = {});


	Settings _settings;

};


}
