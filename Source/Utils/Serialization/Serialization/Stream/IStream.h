#pragma once

#include <cstdint>
#include <ranges>
#include <type_traits>


namespace Inf
{
class ISerializable;

namespace Stream
{
enum class Mode: uint8_t
{
	Load,
	Save
};
}


class IStream
{
	template <class T>
	friend IStream& operator<<(IStream& stream, T& data);


public:
	explicit IStream(const Stream::Mode& mode = Stream::Mode::Load);
	virtual ~IStream();

	virtual bool Open() = 0;
	virtual void Close() = 0;

	Stream::Mode GetMode() const;
	virtual bool IsLoading() const;
	virtual bool IsSaving() const;

	virtual void Serialize(void* ptr, uint64_t size) = 0;


protected:
	void SetMode(const Stream::Mode& mode);


private:
	Stream::Mode _mode;
};


template <class T>
void ToStream(IStream& stream, const T& obj)
{
	stream.Serialize(&obj, sizeof(T));
}

template <class T>
void FromStream(IStream& stream, T& obj)
{
	stream.Serialize(&obj, sizeof(T));
}

template <std::ranges::random_access_range T>
IStream& operator<<(IStream& stream, T& data)
{
	for (auto& i: data)
		stream << i;

	return stream;
}

template <class T>
IStream& operator<<(IStream& stream, T& data)
{
	if constexpr (std::is_base_of_v<ISerializable, T>)
		data.Serialize(stream);
	else
		stream.Serialize(&data, sizeof(T));

	return stream;
}
}
