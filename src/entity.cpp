#include "MEGEngine/entity.h"
#include "MEGEngine/transform.h"
#include "MEGEngine/mesh_renderer.h"
#include "MEGEngine/utils/log.h"

#include "MEGEngine/scripted_behaviour.h"

namespace MEGEngine {
	Entity::Entity() {
		addComponent<Transform>();
	}

	void Entity::callOnStart(std::type_index type) {
		if (auto script = dynamic_cast<ScriptedBehaviour*>(_componentLookup[type])) {
			script->onStart();
		}
	}

	void Entity::addChild(Entity& child) {
		if (child._parent) {
			auto& siblings = child._parent->_children;
			for (unsigned i = 0; i < siblings.size(); i++) {
				if (siblings[i] == &child) {
					siblings.erase(siblings.begin() + i);
				}
			}
		}

		child._parent = this;
		_children.push_back(&child);
	}

	const std::vector<Entity*>& Entity::children() const { return _children; }

	Entity *Entity::parent() const { return _parent; }
}
