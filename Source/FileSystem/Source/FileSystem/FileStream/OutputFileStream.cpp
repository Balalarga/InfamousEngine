#include "OutputFileStream.h"

#include <cassert>

OutputFileStream::OutputFileStream(const std::string& filepath, bool bAutoClose):
	IFileStream(filepath, bAutoClose)
{
	OutputFileStream::Open(filepath);
}

OutputFileStream::OutputFileStream(const std::string& filepath, FileStreamDataMode mode, bool bAutoClose):
	IFileStream(filepath, mode, bAutoClose)
{
	OutputFileStream::Open(filepath);
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

void OutputFileStream::Close()
{
	_stream.close();
	SetOpened(false);
}
