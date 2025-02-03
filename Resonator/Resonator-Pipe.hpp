/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <memory>
#include <cmath>
#include "../Data/Data-Buffer.hpp"
#include "../Filter/Filter-Convolution.hpp"
#include "../Delay/Delay-Recursion.hpp"
#include "../Delay/Delay-Lagrange.hpp"

namespace MilletDSP::Resonator {

class Pipe {
public:
	Pipe(
		double sampleRate = 44100,
		float frequency = 110.0f
	)
	: recur(0.999f)
	{
		const size_t firSize = static_cast<size_t>(sampleRate / 1260);
	  Data::Buffer firCoeffs = Data::Buffer(firSize);
		firCoeffs.fill(1.0f/firSize);
		convolution = Filter::Convolution(firCoeffs);

		// subtract 1.0f to account for the one sample delay of the recursion,
		// and subtract half the FIR size to account for the group delay of the linear phase FIR filter.
		const float delayLength = (static_cast<float>(sampleRate)/frequency) - 1.0f - (static_cast<float>(firSize) / 2.0f);
		delay = Delay::Lagrange<3>(std::ceil(delayLength), delayLength);
	}

	float process(float inputSample) {
		return recur.process(delay.process(convolution.process(inputSample + recur.feedback())));
	}

private:
  Filter::Convolution convolution;
	Delay::Recursion recur;
	Delay::Lagrange<3> delay;
}; // Pipe class

} // MilletDSP::Resonator namespace
