/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Sawtooth.h"

namespace MilletDSP::Generator {

Sawtooth::Sawtooth(double sampleRate, double frequency)
: sampleRate_(sampleRate)
, sample_(0)
, step_(2.0 / (sampleRate / frequency))
{}

double Sawtooth::generate() {
	sample_ = sample_ + step_;
	if (sample_ > 1) sample_ = sample_ - 2;
	return sample_;
}

void Sawtooth::setFrequency(double frequency) {
	step_ = 2.0 / (sampleRate_ / frequency);
}

void Sawtooth::zeroPhase() {
	sample_ = 0;
}

} // MilletDSP::Generator namespace
