/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Direct-Form-II Butterworth IIR filter
 * with templated order and runtime adjustable cutoff
 */

#pragma once

#include <array>
#include <cmath>

namespace MilletDSP::Filter {

template <size_t ORDER>
class Lowpass {
public:
  Lowpass(
    double inSampleRate,
    float inCutoff
  )
  : sampleRate(inSampleRate)
  , cutoff(inCutoff)
  , normPoles([&]() -> std::array<double, ORDER> {
      std::array<double, ORDER> temp;
      for(size_t i=0; i<ORDER; i++) { // fill radian/second normalized poles
        double angle = M_PI * ((2.0 * i) + ORDER - 1) / (2.0 * ORDER);
        temp[i] = -std::cos(angle);
      }
      return temp;
    }())
  {
    setCutoff(cutoff);
    delays.fill(0.0f);
  }

  double getCutoff() {
    return cutoff;
  }
  void setCutoff(double cutoff) {
    const double normRadFreq = 2.0 * M_PI * cutoff / sampleRate;
    if (normRadFreq <= 0.0 || normRadFreq >= 2.0 * M_PI) {
      throw std::invalid_argument("Invalid cutoff frequency");
    }
    const double warped = std::tan(normRadFreq);

    // zero out coefficient arrays and set initial gains
    fbCoeffs.fill(0.0);
    ffCoeffs.fill(0.0);
    fbCoeffs[0] = 1.0;
    ffCoeffs[0] = 1.0;

    for (size_t i = 0; i < ORDER; i += 2) {
      if (i + 1 < ORDER) {
        // scale poles for current cutoff
        const double pole1 = normPoles[i] * warped;
        const double pole2 = normPoles[i + 1] * warped;

        // Convert analog poles to digital domain
        const double d1 = (1.0 + pole1) / (1.0 - pole1);
        const double d2 = (1.0 + pole2) / (1.0 - pole2);

        const double denom = 1.0 + (warped * (d1 + d2)) + (warped * warped);

        std::array<double, 3> sectFB = {
          1.0,
          (2.0 * warped * warped - 2.0) / denom,
          (1.0 - (warped * (d1 + d2)) + (warped * warped)) / denom
        };
        std::array<double, 3> sectFF = {
          warped * warped / denom,
          2.0 * warped * warped / denom,
          warped * warped / denom
        };

        // temporary storage for new coeffs as it cascades
        std::array<double, COEFFSSIZE> newFB, newFF;
        newFB.fill(0.0);
        newFF.fill(0.0);

        // convolve
        for (int j = 0; j < COEFFSSIZE; j++) {
          for (int k = 0; k < 3 && j + k < COEFFSSIZE; k++) {
            newFB[j + k] += fbCoeffs[j] * sectFB[k];
            newFF[j + k] += ffCoeffs[j] * sectFF[k];
          }
        }

        fbCoeffs = newFB;
        ffCoeffs = newFF;
      }
      else {
        // scale pole for current cutoff
        const double pole = normPoles[i] * warped;

        // Convert analog pole to digital domain
        const double d = (1.0 + pole) / (1.0 - pole);

        double denom = 1.0 + (warped * d);
        std::array<double, 2> sectFB = {
          1.0,
          ((warped * d) - 1.0) / denom
        };
        std::array<double, 2> sectFF = {
          warped / denom,
          warped / denom
        };

        // temporary storage for new coeffs as it cascades
        std::array<double, COEFFSSIZE> newFB, newFF;
        newFB.fill(0.0);
        newFF.fill(0.0);

        // convolve
        for (int j = 0; j < COEFFSSIZE; j++) {
          for (int k = 0; k < 2 && j + k < COEFFSSIZE; k++) {
            newFB[j + k] += fbCoeffs[j] * sectFB[k];
            newFF[j + k] += ffCoeffs[j] * sectFF[k];
          }
        }

        fbCoeffs = newFB;
        ffCoeffs = newFF;
      }
    }
  }

  float process(float inputSample) {
    // handle feedback
    double feedbackResult = inputSample;
    for (size_t i = 1; i < COEFFSSIZE; i++) {
      feedbackResult += delays[i - 1] * fbCoeffs[i];
    }

    // handle feedforward
    double outputSample = feedbackResult * ffCoeffs[0];
    for (size_t i = 1; i < COEFFSSIZE; i++) {
      outputSample += delays[i - 1] * ffCoeffs[i];
    }

    // progress delays
    delays[0] = feedbackResult;
    for (size_t i = 1; i < ORDER; i++) {
      delays[i] = delays[i - 1];
    }

    return (float)outputSample;
  }

private:
  static constexpr size_t COEFFSSIZE = ORDER + 1;

  double sampleRate;
  double cutoff;

  std::array<double, ORDER> normPoles;
  std::array<double, COEFFSSIZE> fbCoeffs; // feedback coefficients
  std::array<double, COEFFSSIZE> ffCoeffs; // feedforward coefficients
  std::array<float, ORDER> delays;
}; // Lowpass class

} // MilletDSP::Filter namespace
