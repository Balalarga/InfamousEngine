#include <iostream>
#include <gtest/gtest.h>

#include "ResourceManager/ResourceManager.h"
#include "Filesystem/Path.h"


TEST(ResourceManager, Basic)
{
	Inf::ResourceManager manager;

	std::filesystem::path systemPath("E:\\Downloads");
	std::cout << systemPath.root_path().string() << std::endl;
	std::cout << systemPath.has_root_name() << std::endl;
	std::cout << std::filesystem::path("/Game/Asset/../").has_root_name() << std::endl;
	for (auto& part: systemPath)
	{
		std::cout << part;
	}
	std::cout << std::endl;
	Inf::Path myPath(systemPath);
	Inf::Path myPath2(std::filesystem::path("/Game/Asset/../"));
	std::cout << myPath.ToString() << std::endl;
	std::cout << myPath2.ToString() << std::endl;


	EXPECT_FALSE(manager.MountPath("/Game/Asset", "/Game/Asset/"));

	EXPECT_TRUE(manager.MountPath("/Game/Asset/", "/SomeDir/"));
	EXPECT_FALSE(manager.MountPath("/Game/Asset/", "/Resources/"));

	{
		auto dirPath = manager.GetMountedPath("/Game/Asset/");
		auto filePath = manager.GetMountedPath("/Game/Asset");
		EXPECT_NE(dirPath, filePath);
	}

	if (!manager.MountPath("/Game", "/Resources")) {
		std::cout << std::format("/Game does not mounted\n");
	}
	auto path = manager.Get("/Game/Asset/SomeFile.txt");
	std::cout << std::format("/Game/Asset/SomeFile.txt = {}\n", path.generic_string());
}