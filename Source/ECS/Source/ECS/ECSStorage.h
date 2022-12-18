#pragma once
#include <concepts>
#include <memory>
#include <string>
#include <type_traits>
#include <vector>

namespace Inf
{
class Entity;
class Component;

class ECSStorage
{
public:
	using ComponentStorage = std::pair<const type_info*, std::vector<std::shared_ptr<Component>>>;

	static ECSStorage& Self();

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, Entity>, std::shared_ptr<T>>
	static Create(TArgs&& ...args)
	{
		std::shared_ptr<T>& entity = Self()._entities.emplace_back(std::make_shared<T>(std::forward<TArgs>(args...)));
		return std::weak_ptr(entity);
	}

	template<class T>
	std::enable_if_t<std::derived_from<T, Entity>, std::shared_ptr<T>>
	static Create()
	{
		return Self()._entities.emplace_back(std::make_shared<T>());
	}

	template<class T, class ...TArgs>
	std::enable_if_t<std::derived_from<T, Component>, std::shared_ptr<T>>
	static Create(const std::string& name, TArgs&& ...args)
	{
		std::vector<std::shared_ptr<Component>>& store = GetAllComponentsOf<T>();
		store.emplace_back(std::make_shared<T>(name, std::forward<TArgs>(args...)));
		return std::static_pointer_cast<T>(store.back());
	}

	template<class T>
	std::enable_if_t<std::derived_from<T, Component>, std::shared_ptr<T>>
	static Create(const std::string& name)
	{
		std::vector<std::shared_ptr<Component>>& store = GetAllComponentsOf<T>();
		store.emplace_back(std::make_shared<T>(name));
		return std::static_pointer_cast<T>(store.back());
	}

protected:
	template<class T>
	std::enable_if_t<std::derived_from<T, Component>, std::vector<std::shared_ptr<Component>>&>
	static GetAllComponentsOf()
	{
		const type_info* currentInfo = &typeid(T);
		for (auto& [info, store]: Self()._components)
		{
			if (info == currentInfo)
				return store;
		}
		Self()._components.push_back(std::make_pair(currentInfo, std::vector<std::shared_ptr<Component>>()));
		return Self()._components.back().second;
	}

private:
	ECSStorage() = default;

	std::vector<ComponentStorage> _components;
	std::vector<std::shared_ptr<Entity>> _entities;
};
}
