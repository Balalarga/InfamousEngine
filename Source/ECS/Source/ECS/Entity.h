#pragma once
#include <memory>
#include <vector>

#include "Component.h"
#include "ECSStorage.h"

namespace Inf
{
class Entity: public std::enable_shared_from_this<Entity>
{
public:
	Entity() = default;
	virtual ~Entity();

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, Component>, std::weak_ptr<T>>
	AddComponent(const std::string& name, TArgs&& ...args)
	{
		std::shared_ptr<T> comp = ECSStorage::Create<T>(name, args...);
		AddComponent(comp);
		return comp;
	}

	template<class T>
	std::enable_if_t<std::derived_from<T, Component>, std::weak_ptr<T>>
	AddComponent(const std::string& name)
	{
		std::shared_ptr<T> comp = ECSStorage::Create<T>(name);
		AddComponent(comp);
		return comp;
	}

	template<class T>
	void AddComponent(std::shared_ptr<T> comp)
	{
		_components.push_back({&typeid(T), comp});
		comp->Attach(weak_from_this());
	}

	template<class T>
	bool AddUniqueComponent(std::weak_ptr<T> weak_comp)
	{
		if (GetComponentOf<T>())
			return false;

		AddComponent(weak_comp);
		return true;
	}
	template<class T, class ...TArgs>
	std::weak_ptr<T> AddUniqueComponent(TArgs&& ...args)
	{
		if (GetComponentOf<T>())
			return {};

		auto weak_comp = ECSStorage::Create<T>(args...);
		AddComponent(weak_comp);
		return weak_comp;
	}

	template<class T>
	std::weak_ptr<T> AddUniqueComponent()
	{
		if (GetComponentOf<T>())
			return {};

		std::weak_ptr<T> weak_comp = ECSStorage::Create<T>();
		AddComponent(weak_comp);
		return weak_comp;
	}

	std::weak_ptr<Component> GetComponent(const std::string& name)
	{
		for (auto& [info, comp]: _components)
		{
			if (comp->GetName() == name)
				return comp;
		}
		return {};
	}

	template<class T>
	std::weak_ptr<T> GetComponentOf(const std::string& name)
	{
		const auto& currentInfo = typeid(T);
		for (auto& [info, comp]: _components)
		{
			if (*info == currentInfo)
			{
				std::shared_ptr<T> typedComp = std::static_pointer_cast<T>(comp);
				if (typedComp->GetName() == name)
					return typedComp;
			}
		}
		return nullptr;
	}

	template<class T>
	std::weak_ptr<T> GetFirstComponentOf()
	{
		const auto& currentInfo = typeid(T);
		for (auto& [info, comp]: _components)
		{
			if (*info == currentInfo)
				return std::static_pointer_cast<T>(comp);
		}
		return nullptr;
	}

	template<class T>
	std::vector<std::weak_ptr<T>> GetComponentsOf()
	{
		std::vector<std::weak_ptr<T>> components;
		const auto& currentInfo = typeid(T);
		for (auto& [info, comp]: _components)
		{
			if (*info == currentInfo)
				components.push_back(std::static_pointer_cast<T>(comp));
		}
		return components;
	}


private:
	std::vector<std::pair<const type_info*, std::shared_ptr<Component>>> _components;
};
}
