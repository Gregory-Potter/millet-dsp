/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * hzBins[0] is the 0Hz bin
 * hzBins[maxIndex] is the NiquistFrequency bin
 * symHzBins has form: 0Hz a b c NiquistFrequency c b a
 */

#pragma once

#include <cmath>
#include "./Data-Buffer.hpp"

namespace MilletDSP::Data {

class LinearPhaseFIR : public Buffer {
public:
  LinearPhaseFIR(
    Buffer hzBins,
    Buffer::Window window = Buffer::Window::Boxcar
  )
  : Buffer(construct(hzBins, window))
  {}

private:
  static Buffer construct(Buffer hzBins, Window window) {
    Buffer outputBuffer = Buffer((hzBins.size() * 2) - 2);
    Buffer symHzBins = Buffer(outputBuffer.size());

    // copy original bins
    for (size_t i = 0uz; i < hzBins.size(); i++) {
      symHzBins[i] = hzBins[i];
    }

    // add conjugate symmetry
    for (size_t i = 1uz; i < hzBins.size() - 1uz; i++) {
      symHzBins[symHzBins.size() - i] = hzBins[i];
    }

    // inverse discrete fourier transform
    for (size_t i = 0uz; i < outputBuffer.size(); i++) {
      float sum = 0.0f;
      for (size_t k = 0uz; k < symHzBins.size(); k++) {
        sum += symHzBins[k] * std::cos(2.0 * M_PI * k * i / symHzBins.size());
      }
      outputBuffer[i] = sum / symHzBins.size();
    }

    outputBuffer.window(window);

    return outputBuffer;
  }
}; // FIR class

} // MilletDSP::Data namespace
