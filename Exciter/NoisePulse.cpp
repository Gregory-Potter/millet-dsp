/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "NoisePulse.h"

namespace MilletDSP::Exciter {

NoisePulse::NoisePulse(
  double sampleRate,
  double attackLength,
  double releaseLength,
  double cutoffFreq
)
: noise()
, env(
    sampleRate,
    Envelope::Transition::Attack::INTERP::LIN,
    attackLength,
    Envelope::Transition::Release::INTERP::LIN,
    releaseLength
  )
, filter(
    sampleRate,
    cutoffFreq
  )
{}

double NoisePulse::excite() {
  return env.attenuate(filter.process(noise.generate()));
}

void NoisePulse::triggerOn(double velocity) {
  env.triggerOn(velocity);
}

double NoisePulse::getCutoff() {
  return filter.getCutoff();
}

void NoisePulse::setCutoff(double cutoff) {
  filter.setCutoff(cutoff);
}

} // MilletDSP::Exciter namespace
