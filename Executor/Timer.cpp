/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "Timer.h"

namespace MilletDSP::Executor {

Timer::Timer(
  double sampleRate,
  double seconds,
  std::function<double()> func
)
: length_(sampleRate * seconds)
, counter_(0)
, func_(func)
{}

double Timer::handle() {
  if (counter_ == length_) {
    return 0.0f;
  }
  counter_++;
  return func_();
}

void Timer::execute() {
  counter_ = 0;
}

} // MilletDSP::Executor namespace
