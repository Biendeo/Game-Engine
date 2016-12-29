#pragma once

#include "../Component.h"

namespace Biendeo::GameOff2016::Engine::Components {
	class FirstPersonFlyControls : public Component {
		public:
		FirstPersonFlyControls(GameObject* gameObject);
		~FirstPersonFlyControls();

		CFloat MouseSensitivityX();
		CFloat MouseSensitivityX(CFloat mouseSensitivityX);
		CFloat MouseSensitivityY();
		CFloat MouseSensitivityY(CFloat mouseSensitivityY);
		CFloat MovementSpeed();
		CFloat MovementSpeed(CFloat movementSpeed);
		CFloat FastSpeed();
		CFloat FastSpeed(CFloat fastSpeed);

		void Awake() override;
		void LateUpdate(CFloat deltaTime) override;
		void OnActive() override;
		void OnDestroy() override;
		void OnDisable() override;
		void Start() override;
		void Update(CFloat deltaTime) override;

		protected:
		CFloat movementSpeed;
		CFloat fastSpeed;
		CFloat mouseSensitivityX;
		CFloat mouseSensitivityY;

		bool noClip;

		void MoveForward(CFloat amount);
		void MoveBackward(CFloat amount);
		void MoveForwardNoClip(CFloat amount);
		void MoveBackwardNoClip(CFloat amount);
		void StrafeLeft(CFloat amount);
		void StrafeRight(CFloat amount);
		void TurnLeft(CFloat amount);
		void TurnRight(CFloat amount);
		void LookUp(CFloat amount);
		void LookDown(CFloat amount);
		void FlyUp(CFloat amount);
		void FlyDown(CFloat amount);
	};
}