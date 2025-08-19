/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Pipe.h"
#include <cmath>

namespace MilletDSP::Resonator {

Pipe::Pipe(
  double sampleRate = 44100,
  double frequency = 110.0f
)
: convolution([&] {
  const size_t firSize = sampleRate / 1260;
  Data::Buffer firCoeffs = Data::Buffer(firSize);
  firCoeffs.fill(1.0f/firSize);
  return firCoeffs;
}())
, recur(0.999f)
, delay([&] {
  const double length = (sampleRate/frequency) - 1.0 - (static_cast<double>(convolution.size()) / 2.0);
  return Delay::Lagrange<3>(std::ceil(length), length);
}())
{}

double Pipe::process(double inputSample) {
  return recur.process(delay.process(convolution.process(inputSample + recur.feedback())));
}

} // MilletDSP::Resonator namespace
