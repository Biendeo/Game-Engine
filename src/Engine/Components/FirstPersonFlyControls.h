#pragma once

#include "../Component.h"

namespace Biendeo::GameOff2016::Engine::Components {
	class FirstPersonFlyControls : public Component {
		public:
		FirstPersonFlyControls(GameObject* gameObject);
		~FirstPersonFlyControls();

		float MouseSensitivityX();
		float MouseSensitivityX(float mouseSensitivityX);
		float MouseSensitivityY();
		float MouseSensitivityY(float mouseSensitivityY);
		float MovementSpeed();
		float MovementSpeed(float movementSpeed);
		float FastSpeed();
		float FastSpeed(float fastSpeed);

		void Awake() override;
		void LateUpdate(float deltaTime) override;
		void OnActive() override;
		void OnDestroy() override;
		void OnDisable() override;
		void Start() override;
		void Update(float deltaTime) override;

		protected:
		float movementSpeed;
		float fastSpeed;
		float mouseSensitivityX;
		float mouseSensitivityY;

		bool noClip;

		void MoveForward(float amount);
		void MoveBackward(float amount);
		void MoveForwardNoClip(float amount);
		void MoveBackwardNoClip(float amount);
		void StrafeLeft(float amount);
		void StrafeRight(float amount);
		void TurnLeft(float amount);
		void TurnRight(float amount);
		void LookUp(float amount);
		void LookDown(float amount);
		void FlyUp(float amount);
		void FlyDown(float amount);
	};
}