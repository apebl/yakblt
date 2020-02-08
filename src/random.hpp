/* random.hpp
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

#ifndef __BLT_RANDOM_H__
#define __BLT_RANDOM_H__

#include <climits>
#include <limits>
#include <cfloat>
#include <random>
#include <functional>

using namespace std;

namespace yakblt {
	class Random {
	public:
		Random ();
		Random (long long int seed);

		void setSeed (long long int seed);

		/**
		 * @return a pseudorandom float value between the start (inclusive) and
		 * the end (exclusive)
		 */
		int intRange (int start = INT_MIN, int end = INT_MAX);
		float floatRange (float start = std::numeric_limits<float>::min(),
				float end = std::numeric_limits<float>::max());
		bool boolean ();
		/**
		 * @return a pseudorandom float value between zero (inclusive) and
		 * one (exclusive)
		 */
		float randFloat ();

	private:
		function<float(void)> _generator;
	};
}

#endif
