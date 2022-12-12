#include "IFileStream.h"

IFileStream::IFileStream(std::string filepath, bool bAutoClose):
	_bAutoClose(bAutoClose),
	_filepath(std::move(filepath))
{
	
}

IFileStream::IFileStream(std::string filepath, FileStreamDataMode mode, bool bAutoClose):
	_bAutoClose(bAutoClose),
	_filepath(std::move(filepath)),
	_mode(mode)
{
}

bool IFileStream::Open(const std::string& filepath, bool bReopen)
{
	if (!bReopen && _bOpened)
		return false;
	
	_filepath = filepath;
	return true;
}

void IFileStream::SetMode(FileStreamDataMode mode)
{
	_mode = mode;
}
