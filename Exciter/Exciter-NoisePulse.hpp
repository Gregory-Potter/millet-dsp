/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "../Generator/Noise.h"
#include "../Envelope/Envelope-AR.hpp"
#include "../Filter/Filter-Lowpass.hpp"

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

  float excite() {
    return env.attenuate(noise.generate());
  }

  void triggerOn(float velocity) {
    env.triggerOn(velocity);
  }

private:
  Generator::Noise noise;
  Envelope::AR env;
  Filter::Lowpass<2> filter;
};

} // MilletDSP::Exciter namespace
