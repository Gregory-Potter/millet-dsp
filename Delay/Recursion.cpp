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

#include "Recursion.h"

namespace MilletDSP::Delay {

Recursion::Recursion(float feedback)
: feedbackAttenutation(feedback)
, sample(0.0f)
{}

float Recursion::process(float inputSample) {
  float outputSample = sample;
  sample = inputSample;
  return outputSample;
}

float Recursion::feedback() const {
  return sample * feedbackAttenutation;
}

} // MilletDSP::Delay namespace