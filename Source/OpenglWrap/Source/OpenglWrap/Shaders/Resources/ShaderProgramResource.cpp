#include "ShaderProgramResource.h"

#include <utility>

#include "ShaderResource.h"
#include "ResourceManager/ResourceManager.h"
#include "Shaders/ShaderProgram.h"

namespace Inf
{
ShaderProgramResource::ShaderProgramResource(std::string resourcePath, const std::string& text):
	JsonResource(std::move(resourcePath), text)
{
}

std::shared_ptr<ShaderProgramResource> ShaderProgramResource::LoadFrom(const FileInfo& info)
{
	std::optional<std::string> data = FileSystem::ReadAllFile(info.path);
	if (data.has_value())
	{
		auto resource = std::make_shared<ShaderProgramResource>(info.path, data.value());
		if (!resource->GetJson().IsObject())
			return nullptr;

		rapidjson::Document& json = resource->GetJson();
		bool verification = true;

		verification &= json.HasMember("vertex") && json["vertex"].IsString();
		verification &= json.HasMember("fragment") && json["fragment"].IsString();
		if (json.HasMember("geometry"))
			verification &= json["geometry"].IsObject();

		if (!verification)
			return nullptr;

		std::string vShaderPath = json["vertex"].GetString();
		std::string fShaderPath = json["fragment"].GetString();
		std::string gShaderPath = json.HasMember("geometry") ? json["geometry"].GetString() : "";

		std::shared_ptr vShader = ResourceManager::LoadResource<ShaderResource>(vShaderPath);
		std::shared_ptr fShader = ResourceManager::LoadResource<ShaderResource>(fShaderPath);
		std::shared_ptr gShader = ResourceManager::LoadResource<ShaderResource>(gShaderPath);

		if (!vShader)
			Logger::Error(fmt::format("Couldn't find {} resource for {} ShaderProgram", vShaderPath, info.name));

		if (!fShader)
			Logger::Error(fmt::format("Couldn't find {} resource for {} ShaderProgram", fShaderPath, info.name));

		if (!vShader || !fShader)
			return nullptr;

		resource->_program = std::make_shared<ShaderProgram>(
			vShader->Take(),
			fShader->Take(),
			gShader ? gShader->Take() : nullptr);

		return resource;
	}

	return nullptr;
}
}
