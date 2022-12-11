#pragma once
#include <fstream>
#include <string>

class FileStream
{
public:
	FileStream(std::string filepath, bool bAutoClose = true);
	FileStream() = default;

	virtual ~FileStream() = default;
	
	virtual bool Open(const std::string& filepath, bool bReopen = true);
	virtual void Close() = 0;
	
	bool IsOpened() const { return _bOpened; }
	bool IsAutoClose() const { return _bAutoClose; }
	const std::string& GetFilepath() const { return _filepath; }
	
	operator bool() const { return IsOpened(); }
	
	
protected:
	void SetOpened(bool bState) { _bOpened = bState; }
	
private:
	const bool _bAutoClose = true;
	
	std::string _filepath;
	
	bool _bOpened = false;
};

class InputFileStream: public FileStream
{
public:
	InputFileStream(const std::string& filepath, bool bAutoClose = true);
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

protected:
	std::ifstream _stream;
};

class OutputFileStream: public FileStream
{
public:
	OutputFileStream(const std::string& filepath, bool bAutoClose = true);
	OutputFileStream() = default;
	~OutputFileStream() override;
	
	bool Open(const std::string& filepath, bool bReopen = true) override;
	void Close() override;

	template<class T>
	OutputFileStream& operator<<(T& data)
	{
		_stream << data;
		return *this;
	}

protected:
	std::ofstream _stream;
};

