#include "FileStream.h"

namespace Inf
{
FileStream::FileStream(const std::filesystem::path& path, const Stream::Mode& mode): IStream(mode)
{
	int openFlags = std::ios::binary;
	switch (GetMode())
	{
	case Stream::Mode::Load:
		openFlags |= std::ios::in;
		break;
	case Stream::Mode::Save:
		openFlags |= std::ios::out;
		break;
	}
	_fstream.open(path, openFlags);
	_isOpened = _fstream.is_open();
}

bool FileStream::IsValid() const
{
	return _isOpened;
}

FileStream::operator bool() const
{
	return IsValid();
}

void FileStream::Serialize(void* ptr, int64_t len)
{
	if (!IsValid())
		return;
	
	switch (GetMode())
	{
	case Stream::Mode::Load:
		_fstream.read(static_cast<char*>(ptr), len);
	case Stream::Mode::Save:
		_fstream.write(static_cast<char*>(ptr), len);
		break;
	}
}
}
