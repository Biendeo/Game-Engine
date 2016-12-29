#pragma once

// OS detection
#if defined(_WIN64) || defined(_WIN32)
	#define OS_WINDOWS
#elif defined(__APPLE__) // TODO: Confirm whether this gets just Macs, I think it gets iOS too.
	#define OS_MAC
	#pragma message("Mac compatability has not yet been added, you will get errors.")
#elif defined(__linux__)
	#define OS_LINUX
	#pragma message("Linux compatability has not yet been added, you will get errors.")
#elif defined(__unix__)
	#define OS_UNIX
	#pragma message("Unix compatability has not yet been added, you will get errors.")
#else
	#error "Can't detect OS, terminating compilation. Force with directive OS_[YOUR OS]."
#endif

// CPU detection
#if defined(_WIN64)
	#define CPU_64
#elif defined(_WIN32)
	#define CPU_32
#elif defined(__x86_64__) || defined(__ppc64__) // TODO: Find out what the Unix 32-bit version is.
	#define CPU_64
#else
	#define CPU_32
	#pragma message("Can't detect CPU. Defaulting to 32-bit.")
#endif

#if (defined(CPU_64) || defined(FORCE_DOUBLE_PRECISION)) && !defined(FORCE_SINGLE_PRECISION)
	// CFloats are compiler specific floats. Right now, they are doubles.
	typedef double CFloat;
	// CUints are compiler specific unsigned integers. They are 8 bytes right now.
	typedef uint64_t CUint;
	// CInts are compiler specific integers. They are 8 bytes right now.
	typedef int64_t CInt;
#else
	// CFloats are compiler specific floats. Right now, they are floats.
	typedef float CFloat;
	// CUints are compiler specific unsigned integers. They are 4 bytes right now.
	typedef uint32_t CUint;
	// CInts are compiler specific integers. They are 4 bytes right now.
	typedef int32_t CInt;
#endif