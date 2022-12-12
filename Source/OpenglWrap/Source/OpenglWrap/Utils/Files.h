#pragma once
#include <string>

namespace ogw::Files
{
std::string ReadFile(const std::string& filepath);
void CreateOrOpenFile(std::ofstream& stream, const std::string& filepath);
}
