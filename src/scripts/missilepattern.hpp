#ifndef __BLT_MISSILEPATTERN_H__
#define __BLT_MISSILEPATTERN_H__

#include "../scripter.hpp"

namespace blt {
	class MissilePattern : public Scripter {
	public:
		virtual void init () override;
	};
}

#endif