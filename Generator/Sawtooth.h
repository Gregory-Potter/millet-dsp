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
	Sawtooth(double sampleRate, float frequency);
	
	float generate();
	void setFrequency(float frequency);
	void zeroPhase();
	
private:
  float sample_;
  double sampleRate_;
	float step_;
}; // Sawtooth class

} // MilletDSP::Generator namespace