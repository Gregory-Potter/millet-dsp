/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "../Data/Buffer.h"

namespace MilletDSP::Other {

class Convolution {
public:
  Convolution() = delete;
	Convolution(Data::Buffer inCoeffs);

	double process(double inputSample);
	size_t size() const;
	
private:
	Data::Buffer coeffs;
	Data::Buffer buffer;
	size_t writeIndex;
}; // Convolution class

} // MilletDSP::Other namespace
