/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * A single sample delay that allows for feeding back a signal with other processing in between.
 * For longer delay lengths, place another delay in the feedback loop, and subtract one sample
 * from that delay's length, to account for the single sample delay of the recursion.
 */

#pragma once

namespace MilletDSP::Delay {

class Recursion {
public:
	Recursion(float feedback)
	: feedbackAttenutation(feedback)
	, sample(0.0f)
	{}
	
	float process(float inputSample) {
		float outputSample = sample;
		sample = inputSample;
		return outputSample;
	}
	
	float feedback() const {
		return sample * feedbackAttenutation;
	}
	
private:
	float feedbackAttenutation;
	float sample;
}; // Recursion class

} // MilletDSP::Delay namespace