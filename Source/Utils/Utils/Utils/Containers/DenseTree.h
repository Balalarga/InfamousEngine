#pragma once
#include <map>
#include <span>
#include <type_traits>
#include <vector>

namespace Inf
{

template <class TKey, class TValue>
	requires std::is_trivially_copyable_v<TValue>
class DenseTree
{
public:
	using TKey = TKey;
	using TValue = TValue;


	struct Node
	{
		std::map<TKey, Node> subNodes;
		TValue data;
	};


	TValue* Find(const std::span<TKey>& keys)
	{
		return FindIn(_nodes);
	}


protected:
	TValue* FindIn(std::map<TKey, Node>& nodes, const std::span<TKey>& keys)
	{
		auto it = nodes.find(keys.begin());
		if (it == nodes.end())
			return nullptr;
		return FindIn(it->subNodes, keys.subspan(1));
	}


private:
	std::map<TKey, Node> _nodes;
};

}
