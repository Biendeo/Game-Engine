#include "Framerate.h"

#include <thread>

#include <GLFW/glfw3.h>

namespace Biendeo::GameOff2016::Engine {
	Framerate::Framerate(short expectedFPS) {
		this->expectedFPS = expectedFPS;
		this->frameCount = 0ull;
		UpdateDrawTimes();
		this->delta = static_cast<CFloat>(0.0f);
	}

	void Framerate::SleepToNextSwapBuffer() {
		CFloat currentTime = static_cast<CFloat>(glfwGetTime());
		auto nanos = static_cast<uint64_t>((nextDraw - currentTime) * static_cast<CFloat>(1000000000.0));
		std::this_thread::sleep_for(std::chrono::nanoseconds(nanos));
	}

	void Framerate::UpdateDrawTimes() {
		CFloat previousDraw = this->lastDraw;
		this->lastDraw = static_cast<CFloat>(glfwGetTime());
		this->delta = this->lastDraw - previousDraw;
		this->nextDraw = lastDraw + static_cast<CFloat>(1.0) / expectedFPS;
	}

	uint64_t Framerate::IncrementFrameCount() {
		return ++frameCount;
	}

	short Framerate::ExpectedFPS() {
		return expectedFPS;
	}

	short Framerate::ExpectedFPS(short expectedFPS) {
		this->expectedFPS = expectedFPS;
		return expectedFPS;
	}

	uint64_t Framerate::FrameCount() {
		return frameCount;
	}

	CFloat Framerate::Delta() {
		return delta;
	}
}