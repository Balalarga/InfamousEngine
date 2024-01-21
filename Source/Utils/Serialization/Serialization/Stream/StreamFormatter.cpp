#include "StreamFormatter.h"

#include "ISerializable.h"


namespace Inf
{
IStreamFormatter::IStreamFormatter(IStream& stream): _stream(stream)
{
}

void IStreamFormatter::EnterArray()
{
}

void IStreamFormatter::LeaveArray()
{
}

void IStreamFormatter::EnterMap()
{
}

void IStreamFormatter::LeaveMap()
{
}

void IStreamFormatter::Serialize(ISerializable* data)
{
	data->Serialize(_stream);
}

IStream& IStreamFormatter::GetStream()
{
	return _stream;
}


}
