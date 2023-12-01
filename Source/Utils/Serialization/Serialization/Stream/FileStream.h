#pragma once
#include <filesystem>
#include <fstream>
#include "IStream.h"


namespace Inf
{
class FileStream: public IStream
{
public:
	explicit FileStream(const std::filesystem::path& path, const Stream::Mode& mode);

	virtual bool IsValid() const;
	operator bool() const;
	
	void Serialize(void* ptr, int64_t len) override;


private:
	bool _isOpened = false;
	std::fstream _fstream;
};
}
