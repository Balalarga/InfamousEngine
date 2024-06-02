#include <iostream>
#include "Path.h"


namespace Inf {

char Path::DefaultDelimiter = '/';

Path::Path(const std::filesystem::path& path) {
	for (const auto& part: path) {
		// Exclude slashes
		if (part.has_filename()) {
			_path.push_back(part.string());
		} else if (part.has_root_name()) {
			_hasRoot = true;
			_path.push_back(part.string());
		}
	}
}

std::string Path::ToString() const {
	std::stringstream stream;
	if (_hasRoot)
		stream << DefaultDelimiter;

	for (int i = 0; i < _path.size(); ++i) {
		stream << _path[i];
		if (i+1 != _path.size() || !_hasExtension) 
			stream << DefaultDelimiter;
	}
	return stream.str();
}

Path Path::MakeRelative(const Path& root) const {
	Path result;

	//	for (auto& part: root._path) {
	//		
	//		result._path.push_back();
	//
	//	}
	return result;
}
} // Inf