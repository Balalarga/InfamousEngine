#pragma once

namespace Inf
{
class IStream;


class ISerializable
{
public:
	virtual ~ISerializable() = default;
	virtual void Serialize(IStream& Stream) = 0;
};

}