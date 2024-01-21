#pragma once
#include <filesystem>
#include <fstream>
#include "IStream.h"


namespace Inf
{

class FileStream: public IStream
{
public:
	enum class Format
	{
		Binary,
		Text
	};
	explicit FileStream(std::filesystem::path path, const Stream::Mode& mode, Format format = Format::Binary);
	
	virtual ~FileStream();
	
	bool Open() override;
	void Close() override;
	
	virtual bool IsValid() const;
	operator bool() const;

	void Serialize(void* ptr, uint64_t len) override;


private:
	Format _format;
	int _openFlags;
	std::filesystem::path _filepath;
	bool _isOpened = false;
	std::fstream _fstream;
};

}
