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
	, writeIndex(0uz)
	{}

	float process(float inputSample) {
		float outputSample = 0.0f;
		size_t readIndex = writeIndex;

		buffer[writeIndex] = inputSample;

		for (const float coeff : coeffs) {
			outputSample += buffer[readIndex] * coeff;

			if (readIndex == 0) readIndex = coeffs.size() - 1uz;
			else --readIndex;
		}

		if (++writeIndex == buffer.size()) writeIndex = 0uz;

		return outputSample;
	}

	size_t size() {
		return coeffs.size();
	}
	
private:
	Data::Buffer coeffs;
	Data::Buffer buffer;
	size_t writeIndex;
}; // Convolution class

} // MilletDSP::Filter namespace
