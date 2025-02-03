/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include "../Generator/Generator-Noise.hpp"
#include "../Envelope/Envelope-AR.hpp"

namespace MilletDSP::Exciter {

class NoisePulse {
public:
  NoisePulse(double sampleRate, double attackLength, double releaseLength)
  : noise()
  , env(
      sampleRate,
      Envelope::Transition::Attack(sampleRate, Envelope::Transition::Attack::INTERP::LIN, attackLength),
      Envelope::Transition::Release(sampleRate, Envelope::Transition::Release::INTERP::LIN, releaseLength)
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
};

} // MilletDSP::Exciter namespace