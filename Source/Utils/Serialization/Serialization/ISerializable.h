#pragma once


namespace Inf
{

class ISerializable
{
public:
	virtual ~ISerializable() = default;
	virtual void Serialize(class IStream& stream) = 0;
};

}
