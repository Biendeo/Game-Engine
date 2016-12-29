#pragma once

#include <cstdint>

#include "Constants.h"

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

		CFloat Delta();

		protected:
		short expectedFPS;
		CFloat delta;
		CFloat lastDraw;
		CFloat nextDraw;
		uint64_t frameCount; // This must be 64-bits, a 32-bit number could overflow after a few months of constant usage.
	};
}
