#pragma once

#include <memory>
#include <map>

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

#include <GLFW/glfw3.h>

#include "Framerate.h"
#include "GameObject.h"
#include "Input.h"
#include "BaseObjects/Camera.h"

namespace Biendeo::GameOff2016::Engine {
	// The main class for managing the game environment.
	class Engine {
		public:
		// Passes in the program input arguments and makes a new engine.
		Engine(int argc, char* argv[]);
		~Engine();

		// Starts the execution of the engine. This stops when the GLFW window is closed.
		void Run();

		// Removes a GameObject from the engine. Do not call this directly, call
		// GameObject.Destroy(), which will run this instead.
		// Returns whether an object was successfully destroyed or not.
		bool RemoveGameObject(GameObject& gameObject);

		// Returns a pointer referring to the given object. This should be used to conveniently
		// get a reference to an object. If possible, use GameObject.GetPointer() instead.
		std::shared_ptr<GameObject> GetGameObjectPointer(GameObject& gameObject);

		// Returns a pointer to the root object. All objects should be a child of this object
		// in some way.
		std::shared_ptr<GameObject> GetRootObjectPointer();

		protected:
		std::unique_ptr<Framerate> framerate;

		GLFWmonitor* monitor;
		const GLFWvidmode* vidmode;
		GLFWwindow* window;

		bool verbose;

		std::map<uint64_t, std::shared_ptr<GameObject>> gameObjects;
		
		std::weak_ptr<GameObject> rootObject;
		std::weak_ptr<Components::ComCamera> activeCamera;

		// Starts up GLFW.
		bool InitialiseGLFW();
		// Sets up the window used to display the game, with a valid OpenGL context.
		bool InitialiseWindow();

		// Draws the scene to the current active buffer.
		void DrawBuffer();

		// Instantiates a GameObject. The object needs to be a raw pointer, and is then managed by
		// the engine. The return is a weak pointer to the object in the engine.
		std::shared_ptr<GameObject> Instantiate(GameObject* gameObject);

		// Gets a unique new ID for a new GameObject. This will not conflict with any existing IDs.
		uint64_t NewID();

		// Generates a root object. The previous one should be destroyed beforehand.
		void CreateRootObject();
	};
}