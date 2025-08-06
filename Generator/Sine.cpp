/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Sine.h"
#include <cmath>

namespace MilletDSP::Generator {

Sine::Sine(double sampleRate, float frequency) {
	sampleRate = sampleRate;
  sample = 0;
}

float Sine::generate() {
	
	return sample;
}

void Sine::setFrequency(float frequency) {
  
}
void Sine::zeroPhase() {
  
}

} // MilletDSP::Generator namespace
