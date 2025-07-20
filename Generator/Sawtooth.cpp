/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

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

} // MilletDSP::Generator namespace
