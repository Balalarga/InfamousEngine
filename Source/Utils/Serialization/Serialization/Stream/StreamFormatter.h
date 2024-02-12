#pragma once
#include <cstdint>

namespace Inf
{
class IStream;
class ISerializable;


class IStreamFormatter
{
public:
	IStreamFormatter(IStream& stream);
	virtual ~IStreamFormatter() = default;

	virtual void EnterArray();
	virtual void LeaveArray();
	virtual void EnterMap();
	virtual void LeaveMap();


	virtual void Serialize(void* ptr, uint64_t size) = 0;
	virtual void Serialize(uint8_t& data) = 0;
	virtual void Serialize(uint16_t& data) = 0;
	virtual void Serialize(uint32_t& data) = 0;
	virtual void Serialize(uint64_t& data) = 0;
	virtual void Serialize(int8_t& data) = 0;
	virtual void Serialize(int16_t& data) = 0;
	virtual void Serialize(int32_t& data) = 0;
	virtual void Serialize(int64_t& data) = 0;
	virtual void Serialize(float& data) = 0;
	virtual void Serialize(double& data) = 0;
	virtual void Serialize(bool& data) = 0;
	virtual void Serialize(ISerializable* data);

	virtual IStream& GetStream();


private:
	IStream& _stream;
};

}
