/*
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

/*
 * Based on xoshiro256++ pseudorandom number generator.
 * https://en.m.wikipedia.org/wiki/Xorshift#xoshiro
 * generate() outputs random float values from -1 to 1.
 */

#include "Noise.h"
#include <bit>

namespace MilletDSP::Generator {

double Noise::generate() {
  const uint64_t x = state1 + state4;
  const uint64_t result = std::rotl(x, 23) + state1;
  const uint64_t t = state2 << 17;

  state3 ^= state1;
  state4 ^= state2;
  state2 ^= state3;
  state1 ^= state4;
  state3 ^= t;
  state4 = std::rotl(state4, 45);

  return ((result >> 11) * (2.0 / (1ULL << 53))) - 1.0;
}

} // MilletDSP::Generator namespace
