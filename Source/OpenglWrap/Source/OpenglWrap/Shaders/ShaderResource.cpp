#include "ShaderResource.h"

#include <utility>

#include "FileSystem/FileSystem.h"

namespace Inf
{
const std::map<std::string, ShaderType> ShaderResource::sShaderExtensions =
{
	{".vert", ShaderType::Vertex},
	{".frag", ShaderType::Fragment},
	{".geom", ShaderType::Geometry},
	{".pix", ShaderType::Pixel},
	{".tess", ShaderType::Tesselation},
	{".comp", ShaderType::Compute},
};

std::shared_ptr<ShaderResource> ShaderResource::ResourceHandler(const std::string& path)
{
	const std::string type = FileSystem::GetFileExtension(path);
	if (!sShaderExtensions.contains(type))
		return nullptr;

	return nullptr;
}

ShaderResource::ShaderResource(std::string resourcePath):
	IResource(std::move(resourcePath))
{
}
}
