#pragma once

#include <cstdint>

namespace Biendeo::GameOff2016::Engine {
	// Manages
	class Framerate {
		public:
		Framerate(short expectedFPS);

		void SleepToNextSwapBuffer();
		void UpdateDrawTimes();
		uint64_t IncrementFrameCount();

		short ExpectedFPS();
		short ExpectedFPS(short expectedFPS);

		uint64_t FrameCount();

		double Delta();

		protected:
		short expectedFPS;
		double delta;
		double lastDraw;
		double nextDraw;
		uint64_t frameCount;
	};
}
