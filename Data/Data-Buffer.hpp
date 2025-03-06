/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * !!!NOTE: The [] accessor does not do bounds checks to allow for faster performance
 */

#pragma once

#include <initializer_list>
#include <algorithm>
#include <cmath>
#include <stdexcept>

namespace MilletDSP::Data {

class Buffer {
public:
	Buffer() = delete;
	
	explicit Buffer(size_t size)
	: size_(size)
	, data_(new float[size_])
	{
		std::fill(data_, data_ + size_, 0.0f);
	}
	
	Buffer(std::initializer_list<float> list)
	: size_(list.size())
	, data_(new float[size_])
	{
		std::copy(list.begin(), list.end(), data_);
	}
	
	~Buffer() {
		delete[] data_;
	}
	
	// Copy
	Buffer(const Buffer& other)
	: size_(other.size_)
	{
	  data_ = new float[size_];
		std::copy(other.data_, other.data_ + other.size_, data_);
	}
	Buffer& operator=(const Buffer& other) {
	  size_ = other.size_;
	  data_ = new float[size_];
		std::copy(other.data_, other.data_ + other.size_, data_);
		return *this;
	}
	
	// Move
	Buffer(Buffer&& other)
	: data_(other.data_)
	, size_(other.size_)
	{
	  other.data_ = nullptr;
		other.size_ = 0;
	}
	Buffer& operator=(Buffer&& other) {
	  if (this != &other) {
			delete[] data_;
			data_ = other.data_;
			size_ = other.size_;
			other.data_ = nullptr;
			other.size_ = 0;
		}
		return *this;
	}
	
	const float& operator[](size_t index) const {
		return data_[index];
	}
	
	float& operator[](size_t index) {
		return data_[index];
	}
	
	size_t size() const noexcept {
		return size_;
	}

	float* begin() {
	 return data_;
	}
	
	float* end() {
	 return data_ + size_;
	}
	
	void fill(float value) {
		std::fill(data_, data_ + size_, value);
	}

	float rms() {
		float sumOfSquares = 0.0f;
		for (float& sample : *this) {
			sumOfSquares += sample * sample;
		}
		return std::sqrt(sumOfSquares / size_);
	}

	enum class Window {
		Boxcar,
		Hann,
		Hamming,
		Blackman
	};

	void window(Window w) {
  switch (w) {
		case Window::Boxcar: {
			break;
		}
    case Window::Hann: {
      for (size_t i = 0; i < size_; i++) {
        data_[i] *= 0.5 * (1.0 - cos(2.0 * M_PI * i / (size_ - 1)));
      }
      break;
    }
    case Window::Hamming: {
      constexpr float a = 25.0 / 46.0;
      for (size_t i = 0; i < size_; i++) {
        data_[i] *= a - ((1.0 - a) * cos(2.0 * M_PI * i / (size_ - 1)));
      }
      break;
    }
    case Window::Blackman: {
      constexpr float a0 = 7938.0 / 18608.0;
      constexpr float a1 = 9240.0 / 18608.0;
      constexpr float a2 = 1430.0 / 18608.0;
      for (size_t i = 0; i < size_; i++) {
        data_[i] *= a0 - (a1 * cos(2.0 * M_PI * i / (size_ - 1))) + (a2 * cos(4.0 * M_PI * i / (size_ - 1)));
      }
      break;
    }
  }
}
	
private:
	size_t size_;
	float* data_;
}; // Buffer class

} // MilletDSP::Data namespace
