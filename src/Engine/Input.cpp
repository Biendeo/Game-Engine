#include "Input.h"

namespace Biendeo::GameOff2016::Engine::Input {
	// I'm not a big fan of doing this, but GLFW uses a singleton design to input.
	static const int MAXIMUM_KEYS = 512;
	static const int MAXIMUM_MOUSEBUTTONS = 16;

	std::array<bool, MAXIMUM_KEYS> previousKeyState;
	std::array<bool, MAXIMUM_KEYS> currentKeyState;
	std::array<bool, MAXIMUM_KEYS> futureKeyState;

	std::array<bool, MAXIMUM_MOUSEBUTTONS> previousMouseButtonState;
	std::array<bool, MAXIMUM_MOUSEBUTTONS> currentMouseButtonState;
	std::array<bool, MAXIMUM_MOUSEBUTTONS> futureMouseButtonState;

	int previousMouseX;
	int previousMouseY;
	int currentMouseX;
	int currentMouseY;
	int futureMouseX;
	int futureMouseY;

	bool mouseHidden;
	bool mouseLock;

	void FlushInput() {
		for (bool& b : previousKeyState) {
			b = false;
		}

		for (bool& b : currentKeyState) {
			b = false;
		}

		for (bool& b : futureKeyState) {
			b = false;
		}

		for (bool& b : previousMouseButtonState) {
			b = false;
		}

		for (bool& b : currentMouseButtonState) {
			b = false;
		}

		for (bool& b : futureMouseButtonState) {
			b = false;
		}

		previousMouseX = 0;
		previousMouseY = 0;
		currentMouseX = 0;
		currentMouseY = 0;
		futureMouseX = 0;
		futureMouseY = 0;

		mouseHidden = false;
		mouseLock = false;
	}

	void ConfirmFrameInput() {
		previousKeyState = currentKeyState;
		currentKeyState = futureKeyState;

		previousMouseButtonState = currentMouseButtonState;
		currentMouseButtonState = futureMouseButtonState;

		previousMouseX = currentMouseX;
		currentMouseX = futureMouseX;
		previousMouseY = currentMouseY;
		currentMouseY = futureMouseY;
	}

	bool GetKey(KeyCode key) {
		return currentKeyState.at(key);
	}

	bool GetKeyDown(KeyCode key) {
		return currentKeyState.at(key) && !previousKeyState.at(key);
	}

	bool GetKeyUp(KeyCode key) {
		return !currentKeyState.at(key) && previousKeyState.at(key);
	}

	bool GetMouse(MouseButton button) {
		return currentMouseButtonState.at(button);
	}

	bool GetMouseDown(MouseButton button) {
		return currentMouseButtonState.at(button) && !previousMouseButtonState.at(button);
	}

	bool GetMouseUp(MouseButton button) {
		return !currentMouseButtonState.at(button) && previousMouseButtonState.at(button);
	}

	int GetMouseX() {
		return currentMouseX;
	}

	int GetMouseY() {
		return currentMouseY;
	}

	int GetMouseDeltaX() {
		return currentMouseX - previousMouseX;
	}

	int GetMouseDeltaY() {
		return currentMouseY - previousMouseY;
	}

	bool MouseHidden() {
		return mouseHidden;
	}

	bool MouseHidden(bool mouseHidden) {
		Input::mouseHidden = mouseHidden;
		return mouseHidden;
	}

	bool MouseLock() {
		return mouseLock;
	}

	bool MouseLock(bool mouseLock) {
		Input::mouseLock = mouseLock;
		return mouseLock;
	}

	void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
		if (action == GLFW_PRESS) {
			futureKeyState.at(key) = true;
		} else if (action == GLFW_RELEASE) {
			futureKeyState.at(key) = false;
		}
	}

	void GLFWCursorPosCallback(GLFWwindow* window, double xPos, double yPos) {
		int width, height;
		glfwGetWindowSize(window, &width, &height);

		futureMouseX = xPos;
		futureMouseY = yPos;
	}

	void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
		if (action == GLFW_PRESS) {
			futureMouseButtonState.at(button) = true;
		} else if (action == GLFW_RELEASE) {
			futureMouseButtonState.at(button) = false;
		}
	}
}