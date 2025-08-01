/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace MilletDSP::Generator {

class Sawtooth {
public:
	Sawtooth() = delete;
	Sawtooth(float frequency, float sampleRate);
	
	float generate();
	void reset();
	
private:
	float sample;
	float step;
}; // Sawtooth class

} // MilletDSP::Generator namespace