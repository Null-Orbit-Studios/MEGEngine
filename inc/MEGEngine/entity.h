#ifndef MODEL_H
#define MODEL_H

#include <vector>
#include <unordered_map>

#include "MEGEngine/common.h"
#include "MEGEngine/component.h"
#include "MEGEngine/transform.h"
#include "MEGEngine/mesh_renderer.h"
#include "Utils/log.h"


class ENGINE_API Entity {
public:
	Entity();
	virtual ~Entity() = default;

	void addChild(Entity& child);
	[[nodiscard]] const std::vector<Entity*>& children() const;
	[[nodiscard]] Entity* parent() const;

	template<typename T>
	bool hasComponent() {
		return _componentLookup.find(typeid(T)) != _componentLookup.end();
	}

	template<typename T>
	T* getComponent() {
		auto it = _componentLookup.find(typeid(T));
		if (it == _componentLookup.end()) {
			Log(LogLevel::WRN, "Entity::getComponent<%s>(): Component not found", typeid(T).name());
			return nullptr;
		}

		return static_cast<T*>(it->second);
	}

	const std::vector<std::unique_ptr<Component>>& getComponents() const {
		return _components;
	}

	template<typename T, typename... Args>
	T* addComponent(Args&&... args) {
		if (hasComponent<T>()) {
			Log(LogLevel::WRN, "Entity::addComponent<%s>(): Component already registered", typeid(T).name());
			return nullptr;
		}

		auto component = std::make_unique<T>(std::forward<Args>(args)...);
		T* ptr = component.get();

		_componentLookup[typeid(T)] = ptr;
		_components.push_back(std::move(component));

		_componentLookup[typeid(T)]->_parent = this;

		// if component inherits ScriptBehaviour, call the onStart() function
		callOnStart(typeid(T));

		return ptr;
	}

	template<typename T>
	void removeComponent() {
		auto mapIt = _componentLookup.find(typeid(T));
		if (mapIt == _componentLookup.end()) {
			Log(LogLevel::WRN, "Entity::removeComponent<%s>(): Component not found", typeid(T).name());
			return;
		}

		Component* rawPtr = mapIt->second;

		// match raw pointer to remove from vector
		auto vecIt = std::ranges::find_if(_components, [rawPtr](const std::unique_ptr<Component>& c) {
			return c.get() == rawPtr;
		});

		if (vecIt != _components.end()) {
			_components.erase(vecIt);
		}

		_componentLookup.erase(mapIt);
	}

protected:
	Entity* _parent = nullptr;
	std::vector<Entity*> _children;

	std::vector<std::unique_ptr<Component>> _components;
	std::unordered_map<ComponentTypeID, Component*> _componentLookup;

	void callOnStart(std::type_index type);
};



#endif //MODEL_H