/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace MilletDSP::Generator {

class Sine {
public:
	Sine() = delete;
	Sine(double sampleRate, double frequency);
	
	double generate();
	void setFrequency(double frequency);
	void resetPhase();
	
private:
	double sample;
}; // Sine class

} // MilletDSP::Generator namespace
