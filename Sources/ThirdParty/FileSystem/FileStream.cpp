#include "FileStream.h"

#include <cassert>
#include <sstream>

FileStream::FileStream(std::string filepath, bool bAutoClose):
	_bAutoClose(bAutoClose),
	_filepath(std::move(filepath))
{
	
}

bool FileStream::Open(const std::string& filepath, bool bReopen)
{
	if (!bReopen && _bOpened)
		return false;
	
	_filepath = filepath;
	return true;
}

InputFileStream::InputFileStream(const std::string& filepath, bool bAutoClose):
	FileStream(filepath, bAutoClose)
{
	_stream.open(filepath);
	SetOpened(_stream.is_open());
}

InputFileStream::~InputFileStream()
{
	if (IsAutoClose())
		InputFileStream::Close();
	else
		assert(!IsOpened() && "FileStream didn't closed");
}

bool InputFileStream::Open(const std::string& filepath, bool bReopen)
{
	if (!FileStream::Open(filepath, bReopen))
		return false;
	
	if (IsOpened())
		Close();
	
	_stream.open(filepath);
	SetOpened(_stream.is_open());

	return _stream.is_open();
}

void InputFileStream::Close()
{
	_stream.close();
	SetOpened(false);
}

std::string InputFileStream::ReadRemaining()
{
	if (!IsOpened())
		return "";

	const std::streampos currPos = _stream.tellg();
	_stream.seekg(0, std::ios::end);

	std::string str;
	str.reserve(_stream.tellg());

	_stream.seekg(currPos);

	str.assign(std::istreambuf_iterator(_stream), std::istreambuf_iterator<char>());

	return str;
}

OutputFileStream::OutputFileStream(const std::string& filepath, bool bAutoClose):
	FileStream(filepath, bAutoClose)
{
	_stream.open(filepath);
	SetOpened(_stream.is_open());
}

OutputFileStream::~OutputFileStream()
{
	if (IsAutoClose())
		OutputFileStream::Close();
	else
		assert(!IsOpened() && "FileStream didn't closed");
}

bool OutputFileStream::Open(const std::string& filepath, bool bReopen)
{
	if (!FileStream::Open(filepath, bReopen))
		return false;
	
	if (IsOpened())
		Close();
	
	_stream.open(filepath);
	SetOpened(_stream.is_open());

	return _stream.is_open();
}

void OutputFileStream::Close()
{
	_stream.close();
	SetOpened(false);
}
