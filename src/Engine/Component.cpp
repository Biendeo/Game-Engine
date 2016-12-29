#include "Component.h"

#include "GameObject.h"

namespace Biendeo::GameOff2016::Engine {
	Component::Component(GameObject* gameObject) {
		this->gameObject = gameObject;
	}

	Component::~Component() {

	}
}