#include "Camera.h"

#include <cmath>

namespace Biendeo::GameOff2016::Engine::BaseObjects {
	Camera::Camera(Engine* engine) : Biendeo::GameOff2016::Engine::GameObject(engine) {
		if (!AddComponent(new Components::ComCamera(this))) {
			throw std::exception("A new camera couldn't create a component. Something's wrong.");
		}

		camera = GameObject::GetComponent<Components::ComCamera>();
	}

	Camera::~Camera() {

	}

	std::shared_ptr<Biendeo::GameOff2016::Engine::Components::ComCamera> Camera::CameraComponent() {
		return std::shared_ptr<Biendeo::GameOff2016::Engine::Components::ComCamera>(camera);
	}

}