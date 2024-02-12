#include "BitArray.h"

#include <format>
#include <stdexcept>

BitArray::Iterator& BitArray::Iterator::operator=(bool val)
{
	if (!IsValid())
	{
		throw std::runtime_error(std::format("Trying to set invalid BitArray::Iterator"));
	}

	return *this;
}

BitArray::Iterator& BitArray::Iterator::operator++()
{
	return *this;
}

bool BitArray::Iterator::IsValid() const
{
	return IsValidIdx(blockIdx, bitIdx);
}

BitArray::Iterator::operator bool() const
{
	return IsValid();
}

BitArray::Iterator BitArray::Iterator::Next() const
{
	return {data, idx + 1};
}

BitArray::Iterator::Iterator(std::vector<TBlock>& data, size_t idx):
	data(data), idx(idx), blockIdx(idx / BlockSize), bitIdx(idx % data.size())
{
	if (!IsValidIdx(idx))
	{
		throw std::runtime_error(
			std::format(
				"BitArray::operator[{}] out of range size = {}!!!",
				idx,
				data.size() * BlockSize));
	}
}

void BitArray::Push(bool val)
{
	if (_size >=)

}

void BitArray::Resize(size_t newSize)
{
	_data.resize(newSize / BlockSize);
	_size = _data.size() * sizeof(TBlock);
}

void BitArray::Reserve(size_t newSize)
{
	_data.reserve(newSize / BlockSize);
	_size = _data.size() * sizeof(TBlock);
}

BitArray::Iterator BitArray::operator[](size_t idx)
{
	return {_data, idx};
}

BitArray::ConstIterator BitArray::operator[](size_t idx) const
{
	return {_data, idx};
}

BitArray::Iterator BitArray::begin()
{
	return {_data, 0};
}

BitArray::Iterator BitArray::end()
{
	return {_data, _data.size()};
}

BitArray::ConstIterator BitArray::begin() const
{
	return {_data, 0};
}

BitArray::ConstIterator BitArray::end() const
{
	return {_data, _data.size()};
}
