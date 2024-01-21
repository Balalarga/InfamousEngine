#include "IStream.h"


namespace Inf
{

IStream::IStream(const Stream::Mode& mode):
	_mode(mode)
{
}

IStream::~IStream() = default;

Stream::Mode IStream::GetMode() const
{
	return _mode;
}

bool IStream::IsLoading() const
{
	return _mode == Stream::Mode::Load;
}

bool IStream::IsSaving() const
{
	return _mode == Stream::Mode::Save;
}

void IStream::SetMode(const Stream::Mode& mode)
{
	_mode = mode;
}
}
