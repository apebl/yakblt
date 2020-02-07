#ifndef __BLT_SCORES_H__
#define __BLT_SCORES_H__

#include <vector>
#include <tuple>
#include <string>

using namespace std;

namespace yakblt {
	namespace Scores {
		long get ();
		void add (long score);
		void reset ();
		long getCaptured ();
		void capture ();
		vector<tuple<string, long>> loadScores ();
		void saveScore (const string &name, long score);
	}
}

#endif
