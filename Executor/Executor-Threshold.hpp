/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <functional>
#include <cmath>
#include "../Data/Data-Buffer.hpp"

namespace MilletDSP::Executor {

class Threshold {
public:
  Threshold(
    uint sampleRate
  )
  : buffer(Data::Buffer(sampleRate / 100)) // 10ms length
  , isActive(false)
  {}

  float handle(std::function<float()> func) {
    if (isActive)
    {
      if (buffer.rms() < 0.001f)
      {
        buffer.fill(0.5f);
        isActive = false;
        return 0.0f;
      }
      return func();
    }
    return 0.0f;
  }

  void execute() {
    isActive = true;
  }

private:
  Data::Buffer buffer;
  bool isActive;
}; // Threshold class

} // MilletDSP::Executor namespace
