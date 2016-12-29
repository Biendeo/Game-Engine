#pragma once

#include <memory>

#include "../GameObject.h"
#include "../Components/ComCamera.h"

namespace Biendeo::GameOff2016::Engine::BaseObjects {
	class Camera : public GameObject {
		public:
		Camera(Engine* engine);
		~Camera();
		std::shared_ptr<Biendeo::GameOff2016::Engine::Components::ComCamera> CameraComponent();

		protected:
		std::weak_ptr<Biendeo::GameOff2016::Engine::Components::ComCamera> camera;
	};
}