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
