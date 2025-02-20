/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <memory>
#include <algorithm>
#include "../Data/Data-Buffer.hpp"

namespace MilletDSP::Filter {

class Convolution {
public:
	Convolution(Data::Buffer inCoeffs)
	: coeffs(inCoeffs)
	, buffer(coeffs.size())
	, writeIndex(0)
	{}

	float process(float inputSample) {
		const size_t size = coeffs.size();
		float outputSample = 0.0f;
		size_t readIndex = writeIndex;

		buffer[writeIndex] = inputSample;

		for (const float coeff : coeffs) {
			outputSample += buffer[readIndex] * coeff;

			if (readIndex == 0) readIndex = size - 1;
			else --readIndex;
		}

		if (++writeIndex == size) writeIndex = 0;

		return outputSample;
	}

	size_t size() const {
		return coeffs.size();
	}
	
private:
	Data::Buffer coeffs;
	Data::Buffer buffer;
	size_t writeIndex;
}; // Convolution class

} // MilletDSP::Filter namespace
