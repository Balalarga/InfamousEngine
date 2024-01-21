#pragma once
#include "StreamFormatter.h"

namespace Inf
{

class BinaryFormatter: public IStreamFormatter
{
public:
	void Serialize(void* ptr, uint64_t size) override;
	void Serialize(uint8_t& data) override;
	void Serialize(uint16_t& data) override;
	void Serialize(uint32_t& data) override;
	void Serialize(uint64_t& data) override;
	void Serialize(int8_t& data) override;
	void Serialize(int16_t& data) override;
	void Serialize(int32_t& data) override;
	void Serialize(int64_t& data) override;
	void Serialize(float& data) override;
	void Serialize(double& data) override;
	void Serialize(bool& data) override;
	
};

}