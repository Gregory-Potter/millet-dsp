/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstdint>

namespace MilletDSP::Generator {

class Noise {
public:
	float generate();
	
private:
	uint32_t state1 = 1234;
	uint32_t state2 = 5678;
	uint32_t state3 = 9012;
	uint32_t state4 = 3456;
}; // Noise class

} // MilletDSP::Generator namespace
