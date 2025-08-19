/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Based on xoshiro256++ pseudorandom number generator.
 * https://en.m.wikipedia.org/wiki/Xorshift#xoshiro
 * generate() outputs random float values from -1 to 1.
 */

#pragma once

#include <cstdint>

namespace MilletDSP::Generator {

class Noise {
public:
	double generate();
	
private:
	uint64_t state1 = 1234;
	uint64_t state2 = 5678;
	uint64_t state3 = 9012;
	uint64_t state4 = 3456;
}; // Noise class

} // MilletDSP::Generator namespace
