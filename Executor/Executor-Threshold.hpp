/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <functional>
#include <cmath>
#include "../Data/Buffer.h"

namespace MilletDSP::Executor {

class Threshold {
public:
  Threshold(
    uint sampleRate,
    std::function<float()> func
  )
  : buffer_(Data::Buffer(sampleRate / 100)) // 10ms length
  , writeLoc_(0uz)
  , isActive_(false)
  , func_(func)
  {}

  float handle() {
    if (isActive_) {
      float outputSample = func_();
      buffer_[writeLoc_] = outputSample;
      writeLoc_ = ++writeLoc_ % buffer_.size();
      if (buffer_.rms() < 0.001f) {
        buffer_.fill(0.01f);
        isActive_ = false;
      }
      return outputSample;
    }
    return 0.0f;
  }

  void execute() {
    isActive_ = true;
  }

private:
  Data::Buffer buffer_;
  size_t writeLoc_;
  bool isActive_;
  std::function<float()> func_;
}; // Threshold class

} // MilletDSP::Executor namespace
