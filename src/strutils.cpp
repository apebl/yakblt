#include "strutils.hpp"
#include <algorithm>

namespace yakblt {
	void ltrim (std::string &s) {
		s.erase( s.begin(), std::find_if(s.begin(), s.end(),
				not1(std::ptr_fun<int, int>(isspace))) );
	}

	void rtrim (std::string &s) {
		s.erase( std::find_if(s.rbegin(), s.rend(),
				not1(std::ptr_fun<int, int>(isspace))).base(), s.end() );
	}

	void trim (std::string &s) {
		ltrim(s);
		rtrim(s);
	}
}
