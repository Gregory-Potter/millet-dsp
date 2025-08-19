/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <functional>

namespace MilletDSP::Executor {

class Timer {
public:
  Timer() = delete;
	Timer(
		double sampleRate,
		double seconds,
		std::function<double()> func
	);

	double handle();
	void execute();
	
private:
	std::function<double()> func_;
	size_t length_;
	size_t counter_;
}; // Timer class

} // MilletDSP::Executor namespace
