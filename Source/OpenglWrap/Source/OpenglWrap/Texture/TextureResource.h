#pragma once
#include "Texture2d.h"
#include "ResourceManager/Resources/IResource.h"

namespace Inf
{
class TextureResource: public IResource
{
public:
	static std::shared_ptr<TextureResource> LoadFrom(const FileInfo& info);

	TextureResource(std::string resourcePath, glm::vec2 size, int channels, const unsigned char* data);

	const std::shared_ptr<Texture2d>& Take() const { return _texture; }

private:
	std::shared_ptr<Texture2d> _texture;
};
}
