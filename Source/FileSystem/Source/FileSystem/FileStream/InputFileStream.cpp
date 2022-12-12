#include "InputFileStream.h"

#include <cassert>

InputFileStream::InputFileStream(const std::string& filepath, bool bAutoClose):
	IFileStream(filepath, bAutoClose)
{
	InputFileStream::Open(filepath);
}

InputFileStream::InputFileStream(const std::string& filepath, FileStreamDataMode mode, bool bAutoClose):
	IFileStream(filepath, mode, bAutoClose)
{
	InputFileStream::Open(filepath);
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
	if (!IFileStream::Open(filepath, bReopen))
		return false;

	if (IsOpened())
		Close();

	if (GetMode() == FileStreamDataMode::Binary)
		_stream.setf(std::ios_base::binary);

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
