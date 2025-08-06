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

namespace MilletDSP::Data {

class Buffer {
public:
	Buffer() = delete;
	explicit Buffer(size_t size);
	Buffer(std::initializer_list<float> list);
	~Buffer(); // Destructor
	Buffer(const Buffer& other); // Copy constructor
	Buffer& operator=(const Buffer& other); // Copy assignment operator
	Buffer(Buffer&& other); // Move constructor
	Buffer& operator=(Buffer&& other); // Move assignment operator
	
	const float& operator[](size_t index) const;
	float& operator[](size_t index);
	
	size_t size() const noexcept;
	float* begin();
	float* end();
	
	void fill(float value);
	float rms();
	
	enum class Window {
		Boxcar,
		Hann,
		Hamming,
		Blackman
	};
	
	void window(Window w);
	
private:
	size_t size_;
	float* data_;
}; // Buffer class

} // MilletDSP::Data namespace
