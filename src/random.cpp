/* random.cpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "random.hpp"
#include <chrono>
#include "utils.hpp"

using namespace std;

namespace yakblt {
	Random::Random () {
		default_random_engine engine( std::chrono::system_clock::now().time_since_epoch().count() );
		uniform_real_distribution<float> distribution(0.0f, 1.0f);
		_generator = bind(distribution, engine);
	}

	Random::Random (long long int seed) {
		setSeed(seed);
	}

	void Random::setSeed (long long int seed) {
		default_random_engine engine(seed);
		uniform_real_distribution<float> distribution(0, 1);
		_generator = bind(distribution, engine);
	}

	int Random::intRange (int start, int end) {
		ASSERT(start <= end)
		int dist = end - start;
		int rand = static_cast<int>( dist * randFloat() );
		return start + rand;
	}

	float Random::floatRange (float start, float end) {
		ASSERT(start <= end)
		float dist = end - start;
		float rand = dist * randFloat();
		return start + rand;
	}

	bool Random::boolean () {
		return intRange(0, 2) == 1;
	}

	float Random::randFloat () {
		return _generator();
	}
}
