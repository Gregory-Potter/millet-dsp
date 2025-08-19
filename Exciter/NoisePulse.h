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
  NoisePulse() = delete;
  NoisePulse(
    double sampleRate,
    double attackLength,
    double releaseLength,
    double cutoffFreq
  );

  double excite();
  void triggerOn(double velocity);
  double getCutoff();
  void setCutoff(double cutoff);

private:
  Generator::Noise noise;
  Envelope::AR env;
  Filter::Lowpass<2> filter;
};

} // MilletDSP::Exciter namespace
