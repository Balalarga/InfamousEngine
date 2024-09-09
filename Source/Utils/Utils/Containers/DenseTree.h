#pragma once

#include <functional>
#include <map>
#include <span>
#include <unordered_map>


namespace Inf
{
template <class TInKey, class TInValue>
class DenseTree
{
	struct Node;

public:
	using TKey = TInKey;
	using TValue = TInValue;
	using TContainer = std::map<TKey, Node>;

private:
	struct Node
	{
		TValue data;
		TContainer nodes;
	};

public:
	const TValue* Find(const std::span<const TKey>& keys) const
	{
		return FindAt(_nodes, keys);
	}

	const TValue* Find(const std::vector<TKey>& keys) const
	{
		return Find(std::span(keys));
	}

	const TValue* Find(const TKey& key) const
	{
		return Find({key});
	}

	TValue* Find(const std::span<const TKey>& keys)
	{
		return FindAt(_nodes, keys);
	}

	TValue* Find(const std::vector<TKey>& keys)
	{
		return Find(std::span(keys));
	}

	TValue* Find(const TKey& key)
	{
		return Find({key});
	}

	bool Add(const std::span<const TKey>& keys, const TValue& val)
	{
		return AddAt(_nodes, keys, val);
	}

	bool Add(const std::vector<TKey>& keys, const TValue& val)
	{
		return Add(std::span(keys), val);
	}

	bool Add(const TKey& key, const TValue& val)
	{
		return Add({key}, val);
	}


protected:
	static bool AddAt(TContainer& nodes, std::span<const TKey> keys, const TValue& val)
	{
		if (keys.empty())
		{
			return false;
		}

		auto it = nodes.find(keys.front());
		if (it == nodes.end())
		{
			it = nodes.try_emplace(keys.front()).first;
			if (keys.size() == 1)
			{
				it->second.data = val;
				return true;
			}
		}

		return AddAt(it->second.nodes, keys.subspan(1), val);
	}

	static TValue* FindAt(TContainer& nodes, std::span<const TKey> keys)
	{
		auto it = nodes.find(keys.front());
		if (it == nodes.end())
		{
			return nullptr;
		}

		return FindAt(it->second.nodes, keys.subspan(1));
	}

	static const TValue* FindAt(const TContainer& nodes, std::span<const TKey> keys)
	{
		if (keys.empty())
		{
			return nullptr;
		}

		auto it = nodes.find(keys.front());
		if (it == nodes.end())
		{
			return nullptr;
		}

		if (keys.size() == 1)
		{
			return &it->second.data;
		}

		return FindAt(it->second.nodes, keys.subspan(1));
	}

private:
	TContainer _nodes;
};

template <class TInKey, class TInValue>
class SparseTree
{
	struct Node;

public:
	using TKey = TInKey;
	using TValue = TInValue;
	using TContainer = std::map<TKey, Node>;

private:
	struct Node
	{
		std::optional<TValue> data;
		TContainer nodes;
	};

public:
	const TValue* Find(const std::span<const TKey>& keys) const
	{
		return FindAt(_nodes, keys);
	}

	const TValue* Find(const std::vector<TKey>& keys) const
	{
		return Find(std::span(keys));
	}

	const TValue* Find(const TKey& key) const
	{
		return Find({key});
	}

	TValue* Find(std::vector<TKey> keys)
	{
		return FindAt(_nodes);
	}

	TValue* Find(const TKey& key)
	{
		return Find({key});
	}

	bool Add(const std::vector<TKey>& keys, const TValue& val)
	{
		return AddAt(_nodes, keys, val);
	}

	bool Add(const TKey& key, const TValue& val)
	{
		return Add({key}, val);
	}

	bool Set(const std::vector<TKey>& keys, const TValue& val)
	{
		return SetAt(_nodes, keys, val);
	}

	bool Set(const TKey& key, const TValue& val)
	{
		return Set({key}, val);
	}


protected:
	static bool AddAt(TContainer& nodes, std::span<const TKey> keys, const TValue& val)
	{
		if (keys.empty())
		{
			return false;
		}

		auto it = nodes.find(keys.front());
		if (it == nodes.end())
		{
			it = nodes.try_emplace(keys.front(), std::nullopt).first;
		}

		if (keys.size() == 1)
		{
			if (it->second.data.has_value())
			{
				return false;
			}

			it->second.data = val;
			return true;
		}

		return AddAt(it->second.nodes, keys.subspan(1), val);
	}

	static bool SetAt(TContainer& nodes, std::span<const TKey> keys, const TValue& val)
	{
		if (keys.empty())
		{
			return false;
		}

		auto it = nodes.find(keys.front());
		if (it == nodes.end())
		{
			it = nodes.try_emplace(keys.front(), std::nullopt).first;
		}

		if (keys.size() == 1)
		{
			it->second.data = val;
			return true;
		}

		return AddAt(it->second.nodes, keys.subspan(1), val);
	}

	static TValue* FindAt(TContainer& nodes, std::span<const TKey> keys)
	{
		auto it = nodes.find(keys.front());
		if (it == nodes.end())
		{
			return nullptr;
		}

		return FindAt(it->second.nodes, keys.subspan(1));
	}

	static const TValue* FindAt(const TContainer& nodes, std::span<const TKey> keys)
	{
		if (keys.empty())
		{
			return nullptr;
		}

		auto it = nodes.find(keys.front());
		if (it == nodes.end())
		{
			return nullptr;
		}

		if (keys.size() == 1 && it->second.data.has_value())
		{
			return &it->second.data.value();
		}

		return FindAt(it->second.nodes, keys.subspan(1));
	}

private:
	TContainer _nodes;
};
} // namespace Inf