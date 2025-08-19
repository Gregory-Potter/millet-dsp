/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Threshold.h"

namespace MilletDSP::Executor {

Threshold::Threshold(
  uint sampleRate,
  std::function<double()> func
)
: buffer_(Data::Buffer(sampleRate / 100)) // 10ms length
, writeLoc_(0uz)
, isActive_(false)
, func_(func)
{}

double Threshold::handle() {
  if (isActive_) {
    double outputSample = func_();
    buffer_[writeLoc_] = outputSample;
    writeLoc_ = ++writeLoc_ % buffer_.size();
    if (buffer_.rms() < 0.001) {
      buffer_.fill(0.01);
      isActive_ = false;
    }
    return outputSample;
  }
  return 0.0;
}

void Threshold::execute() {
  isActive_ = true;
}

} // MilletDSP::Executor namespace
