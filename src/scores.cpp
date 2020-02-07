#include "scores.hpp"
#include "utils.hpp"
#include "strutils.hpp"
#include <fstream>
#include <algorithm>
#include <cstdlib>
#include <cstring>

namespace {
#ifdef _WIN32
	const string separator = "\\";
#else
	const string separator = "/";
#endif

	long _score = 0;
	long _captured = 0;
	const string file = ".yakblt-scores.txt";

	bool comp (tuple<string, long> &a, tuple<string, long> &b) {
		return get<1>(a) > get<1>(b);
	}

	const string getHomeDir () {
		/* Unix */
		char *path = getenv("HOME");
		if (path != NULL) {
			return string(path);
		}

		/* Windows */
		path = getenv("USERPROFILE");
		if (path != NULL) {
			return string(path);
		}
		path = getenv("HOMEDRIVE");
		char *temp =  getenv("HOMEPATH");
		if (path != NULL && temp != NULL) {
			path = strdup(path);
			ASSERT(path != NULL);
			strcat(path, temp);
			string result = string(path);
			free(path);
			return result;
		}

		ERROR("Failed to get home directory")
	}
}

namespace yakblt {
	namespace Scores {
		long get () {
			return _score;
		}

		void add (long score) {
			_score += score;
		}

		void reset () {
			_score = 0;
		}

		long getCaptured () {
			return _captured;
		}

		void capture () {
			_captured = _score;
		}

		vector<tuple<string, long>> loadScores () {
			ifstream stream { getHomeDir() + separator + file };
			vector<tuple<string, long>> result;
			while (true) {
				string line;
				getline(stream, line);
				if (stream.eof()) { break; }
				else if (!stream) { ERROR("IO Error") }
				size_t pos = line.find(' ');
				long score = stol( line.substr(0, pos) );
				string name = line.substr(pos);
				trim(name);
				result.emplace_back(name, score);
			}
			sort(result.begin(), result.end(), comp);
			return result;
		}

		void saveScore (const string &name, long score) {
			ofstream stream { getHomeDir() + separator + file, ios::out | ios::app };
			stream << score << ' ' << name << endl;
		}
	}
}
