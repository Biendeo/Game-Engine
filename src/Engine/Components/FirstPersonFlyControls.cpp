#include "FirstPersonFlyControls.h"

#include <cmath>

#include "../CommonMath.h"
#include "../GameObject.h"
#include "../Input.h"

namespace Biendeo::GameOff2016::Engine::Components {
	FirstPersonFlyControls::FirstPersonFlyControls(GameObject* gameObject) : Component(gameObject) {
		mouseSensitivityX = 25.0f;
		mouseSensitivityY = 25.0f;
		movementSpeed = 3.0f;
		fastSpeed = 9.0f;
		noClip = true;
	}

	FirstPersonFlyControls::~FirstPersonFlyControls() {

	}

	CFloat FirstPersonFlyControls::MouseSensitivityX() {
		return mouseSensitivityX;
	}

	CFloat FirstPersonFlyControls::MouseSensitivityX(CFloat mouseSensitivityX) {
		this->mouseSensitivityX = mouseSensitivityX;
		return mouseSensitivityX;
	}

	CFloat FirstPersonFlyControls::MouseSensitivityY() {
		return mouseSensitivityY;
	}

	CFloat FirstPersonFlyControls::MouseSensitivityY(CFloat mouseSensitivityY) {
		this->mouseSensitivityY = mouseSensitivityY;
		return mouseSensitivityY;
	}

	CFloat FirstPersonFlyControls::MovementSpeed() {
		return movementSpeed;
	}

	CFloat FirstPersonFlyControls::MovementSpeed(CFloat movementSpeed) {
		this->movementSpeed = movementSpeed;
		return movementSpeed;
	}

	CFloat FirstPersonFlyControls::FastSpeed() {
		return fastSpeed;
	}

	CFloat FirstPersonFlyControls::FastSpeed(CFloat fastSpeed) {
		this->fastSpeed = fastSpeed;
		return fastSpeed;
	}

	void FirstPersonFlyControls::Awake() {

	}

	void FirstPersonFlyControls::LateUpdate(CFloat deltaTime) {

	}

	void FirstPersonFlyControls::OnActive() {

	}

	void FirstPersonFlyControls::OnDestroy() {

	}

	void FirstPersonFlyControls::OnDisable() {

	}

	void FirstPersonFlyControls::Start() {

	}

	void FirstPersonFlyControls::Update(CFloat deltaTime) {
		CFloat speed = movementSpeed;
		if (Input::GetKey(GLFW_KEY_LEFT_SHIFT)) {
			speed = fastSpeed;
		}

		CFloat speedRate = speed / fastSpeed;

		speed *= deltaTime;

		if (Input::GetKey(GLFW_KEY_W) || Input::GetKey(GLFW_KEY_UP)) {
			if (noClip) MoveForwardNoClip(speed);
			else MoveForward(speed);
		} else if (Input::GetKey(GLFW_KEY_S) || Input::GetKey(GLFW_KEY_DOWN)) {
			if (noClip) MoveBackwardNoClip(speed);
			else MoveBackward(speed);
		}

		if (Input::GetKey(GLFW_KEY_A)) {
			StrafeLeft(speed);
		} else if (Input::GetKey(GLFW_KEY_D)) {
			StrafeRight(speed);
		}

		if (Input::GetKey(GLFW_KEY_LEFT)) {
			TurnLeft(mouseSensitivityX * speedRate * deltaTime * 10.0f);
		} else if (Input::GetKey(GLFW_KEY_RIGHT)) {
			TurnRight(mouseSensitivityX * speedRate * deltaTime * 10.0f);
		}

		if (Input::GetKey(GLFW_KEY_R)) {
			LookUp(mouseSensitivityY * speedRate * deltaTime * 10.0f);
		} else if (Input::GetKey(GLFW_KEY_F)) {
			LookDown(mouseSensitivityY * speedRate * deltaTime * 10.0f);
		}

		if (Input::GetKey(GLFW_KEY_T)) {
			FlyUp(speed);
		} else if (Input::GetKey(GLFW_KEY_G)) {
			FlyDown(speed);
		}

		LookDown(Input::GetMouseDeltaY() * mouseSensitivityY * deltaTime);
		TurnRight(Input::GetMouseDeltaX() * mouseSensitivityX * deltaTime);
	}

	void FirstPersonFlyControls::MoveForward(CFloat amount) {
		CFloat mainDirection = static_cast<CFloat>(cos(gameObject->Transform().Rotate().y * PI() / 180.0f));
		CFloat sideDirection = static_cast<CFloat>(sin(gameObject->Transform().Rotate().y * PI() / 180.0f));
		gameObject->Transform().Translate() += glm::vec3(-sideDirection, 0.0, -mainDirection) * static_cast<float>(amount);
	}

	void FirstPersonFlyControls::MoveBackward(CFloat amount) {
		MoveForward(-amount);
	}

	void FirstPersonFlyControls::MoveForwardNoClip(CFloat amount) {
		CFloat mainDirection = static_cast<CFloat>(cos(gameObject->Transform().Rotate().y * PI() / 180.0f));
		CFloat sideDirection = static_cast<CFloat>(sin(gameObject->Transform().Rotate().y * PI() / 180.0f));
		CFloat flyDirection = static_cast<CFloat>(sin(gameObject->Transform().Rotate().x * PI() / 180.0f));
		gameObject->Transform().Translate() += glm::vec3(-sideDirection, 0.0, -mainDirection) * static_cast<float>(amount * (1 - abs(flyDirection)));
		gameObject->Transform().Translate().y += static_cast<float>(flyDirection) * static_cast<float>(amount);
	}

	void FirstPersonFlyControls::MoveBackwardNoClip(CFloat amount) {
		MoveForwardNoClip(-amount);
	}

	void FirstPersonFlyControls::StrafeLeft(CFloat amount) {
		CFloat mainDirection = static_cast<CFloat>(cos(gameObject->Transform().Rotate().y * PI() / 180.0f));
		CFloat sideDirection = static_cast<CFloat>(sin(gameObject->Transform().Rotate().y * PI() / 180.0f));
		gameObject->Transform().Translate() += glm::vec3(-mainDirection, 0.0, sideDirection) * static_cast<float>(amount);
	}

	void FirstPersonFlyControls::StrafeRight(CFloat amount) {
		StrafeLeft(-amount);
	}

	void FirstPersonFlyControls::TurnLeft(CFloat amount) {
		gameObject->Transform().Rotate().y += static_cast<float>(amount);
	}

	void FirstPersonFlyControls::TurnRight(CFloat amount) {
		TurnLeft(-amount);
	}

	void FirstPersonFlyControls::LookUp(CFloat amount) {
		gameObject->Transform().Rotate().x += static_cast<float>(amount);
		if (gameObject->Transform().Rotate().x > 90.0f) {
			gameObject->Transform().Rotate().x = 90.0f;
		} else if (gameObject->Transform().Rotate().x < -90.0f) {
			gameObject->Transform().Rotate().x = -90.0f;
		}
	}

	void FirstPersonFlyControls::LookDown(CFloat amount) {
		LookUp(-amount);
	}

	void FirstPersonFlyControls::FlyUp(CFloat amount) {
		gameObject->Transform().Translate().y += static_cast<float>(amount);
	}

	void FirstPersonFlyControls::FlyDown(CFloat amount) {
		FlyUp(-amount);
	}
}