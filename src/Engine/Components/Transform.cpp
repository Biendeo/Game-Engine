#include "Transform.h"

#include "../CommonMath.h"

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

	glm::mat4 Transform::Matrix() {
		return TranslateMatrix() * RotateMatrix() * ScaleMatrix();
	}

	glm::mat4 Transform::TranslateMatrix() {
		return glm::mat4(1.0f, 0.0f, 0.0f, Translate().x, 0.0f, 1.0f, 0.0f, Translate().y, 0.0f, 0.0f, 1.0f, Translate().z, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	glm::mat4 Transform::RotateMatrix() {
		return glm::mat4(1.0f, 0.0f, 0.0f, 0.0f, 0.0f, Cos(Rotate().x), -Sin(Rotate().x), 0.0f, 0.0f, Sin(Rotate().x), Cos(Rotate().x), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f) * glm::mat4(Cos(Rotate().y), 0.0f, Sin(Rotate().y), 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, -Sin(Rotate().y), 0.0f, Cos(Rotate().y), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f) * glm::mat4(Cos(Rotate().z), -Sin(Rotate().z), 0.0f, 0.0f, Sin(Rotate().z), Cos(Rotate().z), 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	glm::mat4 Transform::ScaleMatrix() {
		return glm::mat4(Scale().x, 0.0f, 0.0f, 0.0f, 0.0f, Scale().y, 0.0f, 0.0f, 0.0f, 0.0f, Scale().z, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	}

	void Transform::Awake() {

	}

	void Transform::LateUpdate(CFloat deltaTime) {
		Rotate().x = ClampAngle((CFloat)Rotate().x);
		Rotate().y = ClampAngle((CFloat)Rotate().y);
		Rotate().z = ClampAngle((CFloat)Rotate().z);
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