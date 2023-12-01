#pragma once
#include <string>

namespace Inf
{
class ISerializable;

namespace Stream
{
enum class Mode: uint8_t
{
	Load, Save
};
}

class IStream
{
	template<class T>
	friend IStream& operator<<(IStream&, T& data);
public:
	explicit IStream(const Stream::Mode& mode = Stream::Mode::Load);
	virtual ~IStream();
	
	Stream::Mode GetMode() const;
	virtual bool IsLoading() const;
	virtual bool IsSaving() const;
	
	virtual void Serialize(void* ptr, int64_t len) {}

	virtual IStream& operator<<(ISerializable& val);
	virtual IStream& operator<<(ISerializable* val);


protected:
	void SetMode(const Stream::Mode& mode);


private:
	Stream::Mode _mode;
};


template<class T>
	requires std::is_fundamental_v<T>
IStream& operator<<(IStream& stream, T& val)
{
	stream.Serialize(&val, sizeof(T));
	return stream;
}


}
