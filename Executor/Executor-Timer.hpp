#pragma once

#include <functional>

namespace MilletDSP::Executor {

class Timer {
public:
	Timer(
		double sampleRate,
		double seconds
	)
	: length_(sampleRate * seconds)
	, counter_(0uz)
	{}

	float handle(std::function<float()> process) {
		if (counter_ == length_) {
			return 0.0f;
		}
		counter_++;
		return process();
	}

	void execute() {
		counter_ = 0;
	}
	
private:
	size_t length_;
	size_t counter_;
}; // Timer class

} // MilletDSP::Executor namespace
