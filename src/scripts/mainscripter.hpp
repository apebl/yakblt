#ifndef __BLT_MAINSCRIPTER_H__
#define __BLT_MAINSCRIPTER_H__

#include "../scripter.hpp"

namespace blt {
	class MainScripter : public Scripter {
	public:
		virtual void init () override;
	};
}

#endif