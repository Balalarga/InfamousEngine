#pragma once
#include <fstream>

#include "IFileStream.h"

class InputFileStream: public IFileStream
{
public:
	InputFileStream(const std::string& filepath, bool bAutoClose = true);
	InputFileStream(const std::string& filepath, FileStreamDataMode mode, bool bAutoClose = true);
	InputFileStream() = default;
	~InputFileStream() override;

	bool Open(const std::string& filepath, bool bReopen = true) override;
	void Close() override;

	std::string ReadRemaining();

	template<class T>
	InputFileStream& operator>>(const T& data)
	{
		_stream >> data;
		return *this;
	}

	std::ifstream& operator*()
	{
		return _stream;
	}

protected:
	std::ifstream _stream;
};
