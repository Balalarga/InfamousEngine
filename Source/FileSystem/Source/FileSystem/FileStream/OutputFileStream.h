#pragma once
#include <fstream>

#include "IFileStream.h"

class OutputFileStream: public IFileStream
{
public:
	OutputFileStream(const std::string& filepath, bool bAutoClose = true);
	OutputFileStream(const std::string& filepath, FileStreamDataMode mode, bool bAutoClose = true);
	OutputFileStream() = default;
	~OutputFileStream() override;

	bool Open(const std::string& filepath, bool bReopen = true) override;
	void Close() override;

	template<class T>
	OutputFileStream& operator<<(T&& data)
	{
		_stream << data;
		return *this;
	}

protected:
	std::ofstream _stream;
};

