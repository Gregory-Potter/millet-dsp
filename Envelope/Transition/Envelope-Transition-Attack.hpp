/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cmath>

namespace MilletDSP::Envelope::Transition {

class Attack {
public:
	enum class INTERP {
		LIN, // linear
		EXP, // exponential growth from -60dB
		EXP_D, // damped exponential growth from -60dB
		COS // cosine
	};

	INTERP interpolation;
	size_t size;
	
	Attack(
		double sampleRate,
		INTERP interpolation,
		double length
	)
	: interpolation(interpolation)
	, size(length * sampleRate)
	{}
	
	float getAttenuation(double index) {
		switch (interpolation) {
			case INTERP::LIN: {
				return index/size;
			}
			case INTERP::EXP: {
				return exp((-index + size) * log(0.001) / size);
			}
			case INTERP::EXP_D: {
				const float c = -9.23341 * (1.0 - (index / size));
				return (1.0 - c) * exp(c);
			}
			case INTERP::COS: {
				return (-cos(M_PI * index / size) * 0.5) + 0.5;
			}
		}
	}
}; // Attack class

} // MilletDSP::Envelope::Transition namespace