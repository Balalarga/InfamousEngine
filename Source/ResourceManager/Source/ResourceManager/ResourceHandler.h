#pragma once
#include <functional>

namespace Inf
{
class Resource;

using ResourceHandler = std::function<std::shared_ptr<Resource>(const std::string&)>;

class DefaultResourceHandlers
{
public:
	static std::shared_ptr<Resource> HandleJson(const std::string& path);


private:
	DefaultResourceHandlers() = delete;
	DefaultResourceHandlers(const DefaultResourceHandlers&) = delete;
	DefaultResourceHandlers(DefaultResourceHandlers&&) = delete;
	~DefaultResourceHandlers() = delete;
};
}