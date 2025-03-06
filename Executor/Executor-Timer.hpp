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
	Timer(
		double sampleRate,
		double seconds,
		std::function<float()> func
	)
	: length_(sampleRate * seconds)
	, counter_(0)
	, func_(func)
	{}

	float handle() {
		if (counter_ == length_) {
			return 0.0f;
		}
		counter_++;
		return func_();
	}

	void execute() {
		counter_ = 0;
	}
	
private:
	std::function<float()> func_;
	size_t length_;
	size_t counter_;
}; // Timer class

} // MilletDSP::Executor namespace
