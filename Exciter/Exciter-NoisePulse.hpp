/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "../Generator/Noise.h"
#include "../Envelope/Envelope-AR.hpp"
#include "../Filter/Butterworth-Lowpass.hpp"

namespace MilletDSP::Exciter {

class NoisePulse {
public:
  NoisePulse(
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

  double excite() {
    return env.attenuate(filter.process(noise.generate()));
  }

  void triggerOn(double velocity) {
    env.triggerOn(velocity);
  }

  double getCutoff() {
    return filter.getCutoff();
  }

  void setCutoff(double cutoff) {
    filter.setCutoff(cutoff);
  }

private:
  Generator::Noise noise;
  Envelope::AR env;
  Filter::Lowpass<2> filter;
};

} // MilletDSP::Exciter namespace
