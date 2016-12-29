#include "Engine.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "BaseObjects/Camera.h"
#include "BaseObjects/Cube.h"
#include "Components/FirstPersonFlyControls.h"

namespace Biendeo::GameOff2016::Engine {
	// The callback method when GLFW errors. This just outputs a message to stderr.
	void GLFWErrorCallback(int error, const char* description) {
		std::cerr << "GLFW Error: " << description << "\n";
	}

	void GLFWWindowSizeCallback(GLFWwindow* window, int width, int height) {
		//std::cout << "Resized window to: " << width << "x" << height << "\n";
	}

	void GLFWWindowPosCallback(GLFWwindow* window, int screenX, int screenY) {
		//std::cout << "Moved window to: " << screenX << "x" << screenY << "\n";

	}

	void GLFWFramebufferSizeCallback(GLFWwindow* window, int width, int height) {
		//std::cout << "Resized frame buffer to: " << width << "x" << height << "\n";
	}

	Engine::Engine(int argc, char* argv[]) {
		// Start off by turning the arguments into a vector.
		std::vector<std::string> arguments(argc);
		for (int i = 0; i < argc; ++i) {
			arguments[i] = argv[i];
		}

		// Set up the command-line variables.
		this->verbose = true;

		for (const std::string& arg : arguments) {
			// The /Q flag makes this program not print output.
			if (arg == "/Q") {
				verbose = false;
			}
		}

		// Then we set up our program.
		if (!InitialiseGLFW()) {
			abort();
		}

		if (!InitialiseWindow()) {
			abort();
		}

		// This prevents GLFW from swapping buffers until it's finished.
		glfwSwapInterval(1);

		// This establishes a framerate.
		// TODO: Custom based on argument?
		framerate = std::unique_ptr<Framerate>(new Framerate(vidmode->refreshRate));

		// Creates a scene root just so we have a basis to start the engine.
		CreateRootObject();
	}

	Engine::~Engine() {
		glfwDestroyWindow(window);

		glfwTerminate();
	}

	void Engine::Run() {
		// TODO: Test GameObject stuff here.
		{
			using namespace BaseObjects;

			auto cameraPtr = Instantiate(new Camera(this));
			cameraPtr->Name("Test Camera");

			activeCamera = std::weak_ptr<Components::ComCamera>(std::static_pointer_cast<Camera>(cameraPtr)->CameraComponent());

			auto cubePtr = Instantiate(new Cube(this));
			cubePtr->Name("Test Cube");

			auto cubePtrTwo = Instantiate(new Cube(this));
			cubePtrTwo->Name("Test Cube 2");
			cubePtrTwo->Parent(cubePtr);

			cubePtrTwo->Transform().Translate() = glm::vec3({1.5f, 1.5f, 1.5f});
			cubePtrTwo->Transform().Rotate() = glm::vec3({45.0f, 45.0f, 45.0f});
			cubePtrTwo->Transform().Scale() = glm::vec3({0.2f, 0.2f, 0.2f});

			class Rotate : public Component {
				public:
				Rotate(GameObject* gameObject) : Component(gameObject) {}
				~Rotate() {}

				void Awake() override {}
				void LateUpdate(float deltaTime) override {}
				void OnActive() override {}
				void OnDestroy() override {}
				void OnDisable() override {}
				void Start() override {}
				void Update(float deltaTime) override {
					gameObject->Transform().Rotate().x += 60.0f * deltaTime;
					gameObject->Transform().Rotate().y += 30.0f * deltaTime;
					gameObject->Transform().Rotate().z += 15.0f * deltaTime;
				}
			};

			cubePtr->AddComponent(new Rotate(cubePtr.get()));
			cubePtrTwo->AddComponent(new Rotate(cubePtrTwo.get()));
			
			cameraPtr->Transform().Translate().z += 4.0f;
			cameraPtr->AddComponent(new Components::FirstPersonFlyControls(cameraPtr.get()));
		}

		while (!glfwWindowShouldClose(window)) {
			std::shared_ptr<GameObject>(rootObject)->Update((float)framerate->Delta());
			std::shared_ptr<GameObject>(rootObject)->LateUpdate((float)framerate->Delta());
			DrawBuffer();
			framerate->SleepToNextSwapBuffer();
			glfwSwapBuffers(window);
			//if (verbose) std::cout << "Frame " << framerate->FrameCount() << "\n";
			framerate->UpdateDrawTimes();
			framerate->IncrementFrameCount();
			Input::ConfirmFrameInput();
			glfwPollEvents();
		}
	}

	bool Engine::InitialiseGLFW() {
		if (!glfwInit()) {
			if (verbose) std::cout << "GLFW couldn't initialize, something is wrong!\n";
			return false;
		} else {
			if (verbose) {
				int major, minor, revision;
				glfwGetVersion(&major, &minor, &revision);
				std::cout << "Using GLFW " << major << "." << minor << "." << revision << "\n";
			}

			// This associates the error callback function just so we can see GLFW errors.
			glfwSetErrorCallback(GLFWErrorCallback);

			return true;
		}
	}

	bool Engine::InitialiseWindow() {
		// Then we get monitor and video properties.
		monitor = glfwGetPrimaryMonitor();
		vidmode = glfwGetVideoMode(monitor);
		glfwWindowHint(GLFW_RED_BITS, vidmode->redBits);
		glfwWindowHint(GLFW_GREEN_BITS, vidmode->greenBits);
		glfwWindowHint(GLFW_BLUE_BITS, vidmode->blueBits);
		glfwWindowHint(GLFW_REFRESH_RATE, vidmode->refreshRate);

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

		const bool borderlessFullscreen = false;

		const char* windowTitle = "Biendeo's Game Off 2016";

		// This is the point when you call glfwWindowHint for features.
		glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_API);

		// Then, we create the window.
		if (borderlessFullscreen) {
			window = glfwCreateWindow(vidmode->width, vidmode->height, windowTitle, monitor, nullptr);
		} else {
			window = glfwCreateWindow(800, 600, windowTitle, nullptr, nullptr);
		}

		glfwMakeContextCurrent(window);

		// This associates the window resize function.
		glfwSetWindowSizeCallback(window, GLFWWindowSizeCallback);
		// This associates the window positioning function.
		glfwSetWindowPosCallback(window, GLFWWindowPosCallback);
		// This the framebuffer resize function.
		glfwSetFramebufferSizeCallback(window, GLFWFramebufferSizeCallback);
		// These set input functions.
		glfwSetKeyCallback(window, Input::GLFWKeyCallback);
		glfwSetCursorPosCallback(window, Input::GLFWCursorPosCallback);
		glfwSetMouseButtonCallback(window, Input::GLFWMouseButtonCallback);

		// We flush the inputs so the program doesn't think anything has happened yet.
		Input::FlushInput();

		if (verbose) {
			std::cout << "OpenGL Version: " << reinterpret_cast<const char*>(glGetString(GL_VERSION)) << "\n";
		}

		return true;
	}

	void Engine::DrawBuffer() {
		// TODO: Turn this into something good.
		glClearColor(0.5f, 0.2f, 0.2f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		glClear(GL_DEPTH_BUFFER_BIT);
		int screenX, screenY, width, height;
		glfwGetWindowPos(window, &screenX, &screenY);
		glfwGetWindowSize(window, &width, &height);
		std::shared_ptr<Components::ComCamera>(activeCamera)->SetupViewCamera(screenX, screenY, width, height);
		std::shared_ptr<GameObject>(rootObject)->Draw();
	}

	std::shared_ptr<GameObject> Engine::Instantiate(GameObject* gameObject) {
		gameObject->ID(NewID());
		gameObjects.insert(std::pair<uint64_t, std::shared_ptr<GameObject>>(gameObject->ID(), std::shared_ptr<GameObject>(gameObject)));

		// If the root object exists, this object will default to being the child of that.
		if (!rootObject.expired()) {
			gameObject->Parent(std::shared_ptr<GameObject>(rootObject));
		}
		return gameObjects.at(gameObject->ID());
	}

	bool Engine::RemoveGameObject(GameObject& gameObject) {
		try {
			std::shared_ptr<GameObject> ptr = gameObjects.at(gameObject.ID());
			gameObjects.erase(ptr->ID());
			return true;
		} catch (std::out_of_range::exception& e) {
			std::cerr << "The engine tried to delete ID: " << gameObject.ID() << " but it didn't exist!\n";
			std::cerr << e.what() << "\n";
		}

		return false;
	}

	std::shared_ptr<GameObject> Engine::GetGameObjectPointer(GameObject& gameObject) {
		return gameObjects.at(gameObject.ID());
	}

	std::shared_ptr<GameObject> Engine::GetRootObjectPointer() {
		return std::shared_ptr<GameObject>(rootObject);
	}

	uint64_t Engine::NewID() {
		static uint64_t id = 1;
		return id++;
	}

	void Engine::CreateRootObject() {
		auto rootObjectPtr = std::shared_ptr<GameObject>(Instantiate(new GameObject(this)));
		rootObjectPtr->Name("Root");
		rootObject = std::weak_ptr<GameObject>(rootObjectPtr);
	}
}