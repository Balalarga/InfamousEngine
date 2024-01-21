#include "FileStream.h"

namespace Inf
{
FileStream::FileStream(std::filesystem::path  path, const Stream::Mode& mode, Format format):
	IStream(mode),
	_format(format),
	_openFlags(format == Format::Binary ? std::ios::binary : 0),
	_filepath(std::move(path))
{
}

FileStream::~FileStream()
{
	_fstream.close();
}

bool FileStream::Open()
{
	switch (GetMode())
	{
	case Stream::Mode::Load:
		_openFlags |= std::ios::in;
		break;
	case Stream::Mode::Save:
		_openFlags |= std::ios::out;
		break;
	}
	_fstream.open(_filepath, _openFlags);
	_isOpened = _fstream.is_open();
	return _isOpened;
}

void FileStream::Close()
{
	_fstream.close();
}

bool FileStream::IsValid() const
{
	return _isOpened;
}

FileStream::operator bool() const
{
	return IsValid();
}

void FileStream::Serialize(void* ptr, uint64_t len)
{
	if (!IsValid())
		return;
	
	switch (GetMode())
	{
	case Stream::Mode::Load:
		_fstream.read(static_cast<char*>(ptr), len);
		break;
	case Stream::Mode::Save:
		_fstream.write(static_cast<char*>(ptr), len);
		break;
	}
}
}
