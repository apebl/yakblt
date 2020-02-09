/* scores.cpp
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
		/* XDG */
		char *path = getenv("XDG_DATA_HOME");
		if (path != NULL) {
			return string(path);
		}

		/* Unix */
		path = getenv("HOME");
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
