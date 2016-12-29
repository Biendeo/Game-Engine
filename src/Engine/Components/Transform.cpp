#include "Transform.h"

namespace Biendeo::GameOff2016::Engine::Components {
	Transform::Transform(GameObject* gameObject) : Component(gameObject) {
		translate = glm::vec3{0.0, 0.0, 0.0};
		rotate = glm::vec3{0.0, 0.0, 0.0};
		scale = glm::vec3{1.0, 1.0, 1.0};
	}

	Transform::~Transform() {

	}

	glm::vec3& Transform::Translate() {
		return translate;
	}

	glm::vec3& Transform::Rotate() {
		return rotate;
	}

	glm::vec3& Transform::Scale() {
		return scale;
	}

	void Transform::Awake() {

	}

	void Transform::LateUpdate(CFloat deltaTime) {

	}

	void Transform::OnActive() {

	}

	void Transform::OnDestroy() {

	}

	void Transform::OnDisable() {

	}

	void Transform::Start() {

	}

	void Transform::Update(CFloat deltaTime) {

	}
}