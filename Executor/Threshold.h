/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <functional>
#include "../Data/Buffer.h"

namespace MilletDSP::Executor {

class Threshold {
public:
  Threshold() = delete;
  Threshold(
    uint sampleRate,
    std::function<double()> func
  );

  double handle();
  void execute();

private:
  Data::Buffer buffer_;
  size_t writeLoc_;
  bool isActive_;
  std::function<double()> func_;
}; // Threshold class

} // MilletDSP::Executor namespace
