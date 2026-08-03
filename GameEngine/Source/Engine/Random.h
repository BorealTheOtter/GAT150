#pragma once
#include <cstdlib>
#include <ctime>

namespace sr
{
	inline int RandomInt() {
		return rand();
	}

	/// <summary>
	/// Get random integer [0, max)
	/// </summary>
	/// <param name="max">exclusive maximum</param>
	/// <returns>Random number between 0 and max - 1</returns>
	inline int RandomInt(int max) {
		return rand() % max;
	}

	/// <summary>
	/// Get random integer [min, max]
	/// </summary>
	/// <param name="min">the minimum value to return</param>
	/// <param name="max">the maximum value to return</param>
	/// <returns>an integer between min and max (inclusive)</returns>
	inline int RandomInt(int min, int max) {
		return min + (rand() % ((max + 1) - min));
	}

	inline float RandomFloat() {
		return (float)(rand()) / RAND_MAX;
	}

	inline float RandomFloat(float max) {
		return RandomFloat() * max;
	}

	inline float RandomFloat(float min, float max) {
		return min + RandomFloat() * (max - min);
	}

	inline void SetSeed() {
		std::srand(static_cast<unsigned int>(std::time(nullptr)));
	}
}