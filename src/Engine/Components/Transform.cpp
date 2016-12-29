#include "Transform.h"

namespace Biendeo::GameOff2016::Engine::Components {
	Transform::Transform(GameObject* gameObject) : Component(gameObject) {
		translate = glm::vec3{0.0f, 0.0f, 0.0f};
		rotate = glm::vec3{0.0f, 0.0f, 0.0f};
		scale = glm::vec3{1.0f, 1.0f, 1.0f};
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

	void Transform::LateUpdate(float deltaTime) {

	}

	void Transform::OnActive() {

	}

	void Transform::OnDestroy() {

	}

	void Transform::OnDisable() {

	}

	void Transform::Start() {

	}

	void Transform::Update(float deltaTime) {

	}
}