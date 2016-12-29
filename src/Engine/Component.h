#pragma once

#include <memory>

namespace Biendeo::GameOff2016::Engine {
	class GameObject;

	class Component {
		public:
		Component(GameObject* gameObject);
		~Component();

		// Gets called before Start when the object is created.
		virtual void Awake() = 0;
		// Gets called after Update every frame.
		virtual void LateUpdate(float deltaTime) = 0;
		// Gets called when the object is made active.
		virtual void OnActive() = 0;
		// Gets called when the object is destroyed.
		virtual void OnDestroy() = 0;
		// Gets called when the object is made inactive.
		virtual void OnDisable() = 0;
		// Gets called when the object is created.
		virtual void Start() = 0;
		// Gets called every frame.
		virtual void Update(float deltaTime) = 0;

		protected:
		GameObject* gameObject;
	};
}