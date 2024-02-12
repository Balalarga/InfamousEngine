#pragma once
#include <vector>


class BitArray
{
public:
	using TBlock = uint8_t;
	static constexpr size_t BlockSize = sizeof(TBlock);


	struct Iterator
	{
		friend class BitArray;

		Iterator& operator=(bool val);
		Iterator& operator++();

		bool IsValid() const;
		operator bool() const;

		Iterator Next() const;


	private:
		Iterator(std::vector<TBlock>& data, size_t idx);

		std::vector<TBlock>& data;
		size_t idx;
		size_t blockIdx;
		size_t bitIdx;
	};


	struct ConstIterator
	{
		friend class BitArray;

		ConstIterator& operator=(bool val);
		ConstIterator& operator++();

		bool IsValid() const;
		operator bool() const;

		ConstIterator Next() const;


	private:
		ConstIterator(const std::vector<TBlock>& data, size_t idx);

		const std::vector<TBlock>& data;
		size_t idx;
		size_t blockIdx;
		size_t bitIdx;
	};


	void Push(bool val);
	void Resize(size_t newSize);
	void Reserve(size_t newSize);


	Iterator operator[](size_t idx);
	ConstIterator operator[](size_t idx) const;
	Iterator begin();
	Iterator end();
	ConstIterator begin() const;
	ConstIterator end() const;


private:
	std::vector<TBlock> _data;
	size_t _size = 0;
};
