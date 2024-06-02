#ifndef INFAMOUSENGINE_PATH
#define INFAMOUSENGINE_PATH

#include <vector>
#include <filesystem>
#include "Containers/DenseTree.h"


namespace Inf {

class Path {
public:
	static char DefaultDelimiter;

	Path() = default;
	Path(Path&&) = default;
	Path(const Path&) = default;
	explicit Path(const std::filesystem::path& path);
	
	std::string ToString() const;
	
	Path MakeRelative(const Path& root) const;


private:
	std::vector<std::string> _path;
	bool _hasRoot = false;
	bool _hasExtension = false;
};

} // Inf

#endif //INFAMOUSENGINE_PATH
