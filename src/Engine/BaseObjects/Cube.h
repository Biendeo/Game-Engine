#pragma once

#include "../GameObject.h"

namespace Biendeo::GameOff2016::Engine::BaseObjects {
	class Cube : public GameObject {
		public:
		Cube(Engine* engine);
		~Cube();

		void DrawSelf() override;
	};
}