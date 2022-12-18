#pragma once
#include <vector>

namespace Inf
{
class BufferLayout
{
public:
	struct VariableInfo
	{
		int Type;
		int Count;
		int64_t Size;
		bool Normalized = true;
	};
	
	BufferLayout& Float(int count);
	BufferLayout& Int(int count);
	BufferLayout& Unsigned(int count);
    
	std::vector<VariableInfo> Variables;
	int Size = 0;
};
}