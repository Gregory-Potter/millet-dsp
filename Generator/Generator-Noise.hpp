/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Based on xoshiro128+ pseudorandom number generator.
 * https://en.m.wikipedia.org/wiki/Xorshift#xoshiro
 * generate() outputs random float values from -1 to 1.
 */

#pragma once

#include <cstdint>

namespace MilletDSP::Generator {

class Noise {
public:
	float generate() {
		// uses top 24 bits as they have better randomness
		const uint32_t intResult = (state1 + state4) >> 8;

		const uint32_t t = state2 << 9;

		state3 ^= state1;
		state4 ^= state2;
		state2 ^= state3;
		state1 ^= state4;
		state3 ^= t;
		state4 = (state4 << 11) | (state4 >> (32 - 11)); // rotate by 11

		return static_cast<float>(intResult) / (float)((1 << 23) - 1) - 1.0f;
	}
	
private:
	uint32_t state1 = 1234;
	uint32_t state2 = 5678;
	uint32_t state3 = 9012;
	uint32_t state4 = 3456;
}; // Noise class

} // MilletDSP::Generator namespace
