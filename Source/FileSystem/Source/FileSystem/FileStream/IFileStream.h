#pragma once
#include <string>

enum class FileStreamDataMode: uint8_t
{
	Text, Binary
};

class IFileStream
{
public:
	IFileStream(std::string filepath, bool bAutoClose = true);
	IFileStream(std::string filepath, FileStreamDataMode mode, bool bAutoClose = true);
	IFileStream() = default;

	virtual ~IFileStream() = default;

	virtual bool Open(const std::string& filepath, bool bReopen = true);
	virtual void Close() = 0;

	void SetMode(FileStreamDataMode mode);
	FileStreamDataMode GetMode() const { return _mode; }

	const std::string& GetFilepath() const { return _filepath; }

	bool IsOpened() const { return _bOpened; }
	bool IsAutoClose() const { return _bAutoClose; }

	operator bool() const { return IsOpened(); }


protected:
	void SetOpened(bool bState) { _bOpened = bState; }

private:
	const bool _bAutoClose = true;
	std::string _filepath;
	FileStreamDataMode _mode = FileStreamDataMode::Text;

	bool _bOpened = false;
};
