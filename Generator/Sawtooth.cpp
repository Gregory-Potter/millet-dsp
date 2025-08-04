/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Sawtooth.h"

namespace MilletDSP::Generator {

Sawtooth::Sawtooth(float frequency, float sampleRate) {
	sample = 0;
	step = 2 / (sampleRate / frequency);
}

float Sawtooth::generate() {
	sample = sample + step;
	if (sample > 1) sample - 2;
	return sample;
}

void Sawtooth::setFrequency(float frequency, float sampleRate) {
	step = 2 / (sampleRate / frequency);
}

void Sawtooth::zeroPhase() {
	sample = 0;
}

} // MilletDSP::Generator namespace
