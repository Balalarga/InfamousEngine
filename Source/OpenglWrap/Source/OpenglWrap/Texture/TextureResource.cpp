#include "TextureResource.h"

#include <utility>

#include "Stb/stb_image.h"

namespace Inf
{
std::shared_ptr<TextureResource> TextureResource::LoadFrom(const FileInfo& info)
{
	stbi_set_flip_vertically_on_load(true);
	glm::ivec2 size;
	int channels;
	stbi_uc* imageData = stbi_load(info.path.c_str(), &size.x, &size.y, &channels, 0);

	if (!imageData)
		return nullptr;

	return std::make_shared<TextureResource>(info.path, size, channels, imageData);
}

TextureResource::TextureResource(std::string resourcePath, glm::vec2 size, int channels, const unsigned char* data):
	IResource(std::move(resourcePath)),
	_texture(std::make_shared<Texture2d>(size, channels, data))
{
}
}
