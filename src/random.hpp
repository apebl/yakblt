#ifndef __BLT_RANDOM_H__
#define __BLT_RANDOM_H__

#include <climits>
#include <limits>
#include <cfloat>
#include <random>
#include <functional>

using namespace std;

namespace blt {
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
