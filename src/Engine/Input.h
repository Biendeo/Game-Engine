#pragma once

#include <array>

#include <Windows.h>
#include <GL/glew.h>
#include <GL/GL.h>

#include <GLFW/glfw3.h>

namespace Biendeo::GameOff2016::Engine {
	namespace Input {
		typedef int KeyCode;
		typedef int MouseButton;

		void FlushInput();
		void ConfirmFrameInput();

		bool GetKey(KeyCode key);
		bool GetKeyDown(KeyCode key);
		bool GetKeyUp(KeyCode key);

		bool GetMouse(MouseButton button);
		bool GetMouseDown(MouseButton button);
		bool GetMouseUp(MouseButton button);

		int GetMouseX();
		int GetMouseY();
		int GetMouseDeltaX();
		int GetMouseDeltaY();

		bool MouseHidden();
		bool MouseHidden(bool mouseHidden);

		bool MouseLock();
		bool MouseLock(bool mouseLock);

		void GLFWKeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void GLFWCursorPosCallback(GLFWwindow* window, double xPos, double yPos);
		void GLFWMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);

		// TODO: Add scroll wheel support.
		// TODO: Add XInput support.
	};
}