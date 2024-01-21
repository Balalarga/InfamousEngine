#include "BinaryFormatter.h"

#include "IStream.h"

void Inf::BinaryFormatter::Serialize(void* ptr, uint64_t size)
{
	GetStream().Serialize(ptr, size);
}

void Inf::BinaryFormatter::Serialize(uint8_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(uint16_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(uint32_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(uint64_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(int8_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(int16_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(int32_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(int64_t& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(float& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(double& data)
{
	GetStream() << data;
}

void Inf::BinaryFormatter::Serialize(bool& data)
{
	GetStream() << data;
}
