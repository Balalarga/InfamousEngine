#pragma once

class IJsonable
{
public:
	virtual ~IJsonable() = default;

	virtual void Serialize() = 0;
	virtual void Deserialize() = 0;
};
