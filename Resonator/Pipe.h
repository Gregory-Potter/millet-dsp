/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "../Other/Convolution.h"
#include "../Delay/Recursion.h"
#include "../Delay/Lagrange.hpp"

namespace MilletDSP::Resonator {

class Pipe {
public:
  Pipe() = delete;
	Pipe(
		double sampleRate = 44100.0,
		double frequency = 110.0
	);

	double process(double inputSample);

private:
	Other::Convolution convolution;
	Delay::Recursion recur;
	Delay::Lagrange<3> delay;
}; // Pipe class

} // MilletDSP::Resonator namespace
