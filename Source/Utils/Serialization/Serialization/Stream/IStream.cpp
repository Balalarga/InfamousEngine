#include "IStream.h"

#include "ISerializable.h"

namespace Inf
{

IStream::IStream(const Stream::Mode& mode):
	_mode(mode)
{
}

IStream::~IStream() = default;

bool IStream::IsLoading() const
{
	return _mode == Stream::Mode::Load;
}

bool IStream::IsSaving() const
{
	return _mode == Stream::Mode::Save;
}

Stream::Mode IStream::GetMode() const
{
	return _mode;
}

IStream& IStream::operator<<(ISerializable& val)
{
	val.Serialize(*this);
	return *this;
}

IStream& IStream::operator<<(ISerializable* val)
{
	val->Serialize(*this);
	return *this;
}

void IStream::SetMode(const Stream::Mode& mode)
{
	_mode = mode;
}

}
