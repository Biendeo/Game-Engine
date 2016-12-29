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

	float FirstPersonFlyControls::MouseSensitivityX() {
		return mouseSensitivityX;
	}

	float FirstPersonFlyControls::MouseSensitivityX(float mouseSensitivityX) {
		this->mouseSensitivityX = mouseSensitivityX;
		return mouseSensitivityX;
	}

	float FirstPersonFlyControls::MouseSensitivityY() {
		return mouseSensitivityY;
	}

	float FirstPersonFlyControls::MouseSensitivityY(float mouseSensitivityY) {
		this->mouseSensitivityY = mouseSensitivityY;
		return mouseSensitivityY;
	}

	float FirstPersonFlyControls::MovementSpeed() {
		return movementSpeed;
	}

	float FirstPersonFlyControls::MovementSpeed(float movementSpeed) {
		this->movementSpeed = movementSpeed;
		return movementSpeed;
	}

	float FirstPersonFlyControls::FastSpeed() {
		return fastSpeed;
	}

	float FirstPersonFlyControls::FastSpeed(float fastSpeed) {
		this->fastSpeed = fastSpeed;
		return fastSpeed;
	}

	void FirstPersonFlyControls::Awake() {

	}

	void FirstPersonFlyControls::LateUpdate(float deltaTime) {

	}

	void FirstPersonFlyControls::OnActive() {

	}

	void FirstPersonFlyControls::OnDestroy() {

	}

	void FirstPersonFlyControls::OnDisable() {

	}

	void FirstPersonFlyControls::Start() {

	}

	void FirstPersonFlyControls::Update(float deltaTime) {
		float speed = movementSpeed;
		if (Input::GetKey(GLFW_KEY_LEFT_SHIFT)) {
			speed = fastSpeed;
		}

		float speedRate = speed / fastSpeed;

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

	void FirstPersonFlyControls::MoveForward(float amount) {
		float mainDirection = (float)cos(gameObject->Transform().Rotate().y * PI() / 180.0f);
		float sideDirection = (float)sin(gameObject->Transform().Rotate().y * PI() / 180.0f);
		gameObject->Transform().Translate() += glm::vec3(-sideDirection, 0.0f, -mainDirection) * amount;
	}

	void FirstPersonFlyControls::MoveBackward(float amount) {
		MoveForward(-amount);
	}

	void FirstPersonFlyControls::MoveForwardNoClip(float amount) {
		float mainDirection = (float)cos(gameObject->Transform().Rotate().y * PI() / 180.0f);
		float sideDirection = (float)sin(gameObject->Transform().Rotate().y * PI() / 180.0f);
		float flyDirection = (float)sin(gameObject->Transform().Rotate().x * PI() / 180.0f);
		gameObject->Transform().Translate() += glm::vec3(-sideDirection, 0.0, -mainDirection) * (amount * (1 - abs(flyDirection)));
		gameObject->Transform().Translate().y += flyDirection * amount;
	}

	void FirstPersonFlyControls::MoveBackwardNoClip(float amount) {
		MoveForwardNoClip(-amount);
	}

	void FirstPersonFlyControls::StrafeLeft(float amount) {
		float mainDirection = (float)cos(gameObject->Transform().Rotate().y * PI() / 180.0f);
		float sideDirection = (float)sin(gameObject->Transform().Rotate().y * PI() / 180.0f);
		gameObject->Transform().Translate() += glm::vec3(-mainDirection, 0.0f, sideDirection) * amount;
	}

	void FirstPersonFlyControls::StrafeRight(float amount) {
		StrafeLeft(-amount);
	}

	void FirstPersonFlyControls::TurnLeft(float amount) {
		gameObject->Transform().Rotate().y += amount;
	}

	void FirstPersonFlyControls::TurnRight(float amount) {
		TurnLeft(-amount);
	}

	void FirstPersonFlyControls::LookUp(float amount) {
		gameObject->Transform().Rotate().x += amount;
		if (gameObject->Transform().Rotate().x > 90.0f) {
			gameObject->Transform().Rotate().x = 90.0f;
		} else if (gameObject->Transform().Rotate().x < -90.0f) {
			gameObject->Transform().Rotate().x = -90.0f;
		}
	}

	void FirstPersonFlyControls::LookDown(float amount) {
		LookUp(-amount);
	}

	void FirstPersonFlyControls::FlyUp(float amount) {
		gameObject->Transform().Translate().y += amount;
	}

	void FirstPersonFlyControls::FlyDown(float amount) {
		FlyUp(-amount);
	}
}