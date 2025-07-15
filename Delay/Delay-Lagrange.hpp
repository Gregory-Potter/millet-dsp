/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Sub-sample delay using Lagrange interpolation
 * with templated order, and runtime adjustable length.
 * Order 1 ≡ linear, Order 2 ≡ quadratic, Order 3 ≡ cubic
 */

#pragma once

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <cmath>
#include "../Data/Buffer.h"

namespace MilletDSP::Delay {

template<size_t order> // requires (order > 0)
class Lagrange {
public:
	Lagrange(
		size_t maxDelay,
		double delay
	)
	: maxDelay_(maxDelay)
	, buffer_(maxDelay_ + order + 1)
	, weights_(order + 1)
	{
		setDelay(delay);
	}

	float process(float inputSample) {
		buffer_[writeIndex_] = inputSample;

		float outputSample = 0.0f;

		size_t readIndex = (writeIndex_ + (buffer_.size() - intDelay_)) % buffer_.size();
		for (float weight : weights_) {
			outputSample += buffer_[readIndex] * weight;
			readIndex = (readIndex == 0) ? buffer_.size() - 1 : readIndex - 1;
		}

		writeIndex_ = ++writeIndex_ % buffer_.size();

		return outputSample;
	}

	float getDelay() const {
		return delay_;
	}

	void setDelay(double length) {
		delay_ = std::clamp(length, static_cast<double>(weights_.size() / 2.0), static_cast<double>(maxDelay_));
		intDelay_ = std::trunc(delay_);

		const double fracDelay = delay_ - intDelay_;
		for (double i=0.0; i<=order; i++) {
		  double weight = 1.0f;
		  for (double j=0.0; j<=order; j++) {
				if (i != j) weight *= (fracDelay - j) / (i - j);
			}
			weights_[i] = weight;
		}

		std::cout << "weights: ";
		for (float weight : weights_) {
		  std::cout << std::setprecision(10) << weight << ", ";
		}
		std::cout << std::endl;
	}

private:
	size_t maxDelay_;
	double delay_;
	size_t intDelay_;

	Data::Buffer buffer_;
	Data::Buffer weights_;

	size_t writeIndex_ = 0;
}; // Lagrange class

} // MilletDSP::Delay namespace
