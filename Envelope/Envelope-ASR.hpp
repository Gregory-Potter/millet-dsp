/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <memory>
#include <algorithm>
#include "./Transition/Envelope-Transition-Attack.hpp"
#include "./Transition/Envelope-Transition-Release.hpp"

namespace MilletDSP::Envelope {

class ASR {
public:
	ASR(
		double sampleRate,
		Transition::Attack::INTERP attackInterp,
		double attackLength,
		Transition::Release::INTERP releaseInterp,
		double releaseLength
	)
	: sampleRate_(sampleRate)
	, attack_(sampleRate, attackInterp, attackLength)
	, release_(sampleRate, releaseInterp, releaseLength)
	, stage_(STAGE::IDLE)
	, index_(0uz)
	{}

	float attenuate(float inputSample) {
		switch(stage_) {
			case STAGE::IDLE: {
				return 0.0f;
			}
			case STAGE::ATTACK: {
				const float outputSample = inputSample * attack_.getAttenuation(index_++) * scaler_;
				if (index_ == attack_.size) setStage(STAGE::RELEASE);
				return outputSample;
			}
			case STAGE::SUSTAIN: {
				return scaler_;
			}
			case STAGE::RELEASE: {
				const float outputSample = inputSample * release_.getAttenuation(index_++) * scaler_;
				if (index_ == release_.size) setStage(STAGE::IDLE);
				return outputSample;
			}
		}
	}

	void triggerOn(float velocity) {
		scaler_ = velocity;
		setStage(STAGE::ATTACK);
	}
	
	void triggerOff() {
		setStage(STAGE::RELEASE);
	}
	
	void setAttackLength(double seconds) {
		const size_t newSize = seconds * sampleRate_;
		if (stage_ == STAGE::ATTACK) {
			index_ = index_ / attack_.size * newSize;
		}
		attack_.size = newSize;
	}
	
	void setReleaseLength(double seconds) {
		const size_t newSize = seconds * sampleRate_;
		if (stage_ == STAGE::RELEASE) {
			index_ = index_ / attack_.size * newSize;
		}
		release_.size = newSize;
	}
	
private:
	enum class STAGE { IDLE, ATTACK, SUSTAIN, RELEASE };

	double sampleRate_;
	Transition::Attack attack_;
	Transition::Release release_;
	float scaler_;
	STAGE stage_;
	size_t index_;
	
	void setStage(STAGE stg) {
		stage_ = stg;
		index_ = 0uz;
	}
}; // ASR class

} // MilletDSP::Envelope namespace
