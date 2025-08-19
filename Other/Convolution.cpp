/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Convolution.h"

namespace MilletDSP::Other {

Convolution::Convolution(Data::Buffer inCoeffs)
: coeffs(inCoeffs)
, buffer(coeffs.size())
, writeIndex(0uz)
{}

double Convolution::process(double inputSample) {
  const size_t size = coeffs.size();
  double outputSample = 0.0;
  size_t readIndex = writeIndex;

  buffer[writeIndex] = inputSample;

  for (const double coeff : coeffs) {
    outputSample += buffer[readIndex] * coeff;

    if (readIndex == 0uz) readIndex = size - 1uz;
    else --readIndex;
  }

  if (++writeIndex == size) writeIndex = 0uz;

  return outputSample;
}

size_t Convolution::size() const {
  return coeffs.size();
}

} // MilletDSP::Other namespace
