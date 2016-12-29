#pragma once

#include <Windows.h>
#include <GL/GL.h>

#include "../Component.h"

namespace Biendeo::GameOff2016::Engine::Components {
	class ComCamera : public Component {
		public:
		ComCamera(GameObject* gameObject);
		~ComCamera();

		bool Perspective();
		bool Perspective(bool perspective);
		CFloat FOV();
		CFloat FOV(CFloat fov);

		void SetupViewCamera(int screenX, int screenY, int width, int height);

		void Awake() override;
		void LateUpdate(CFloat deltaTime) override;
		void OnActive() override;
		void OnDestroy() override;
		void OnDisable() override;
		void Start() override;
		void Update(CFloat deltaTime) override;

		protected:
		bool perspective;
		CFloat fov;
	};
}