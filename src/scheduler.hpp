#ifndef __BLT_SCHEDULER_H__
#define __BLT_SCHEDULER_H__

#include "event.hpp"

namespace yakblt {
	class Scheduler {
	public:
		Scheduler (int frameInterval = 0);
		void reset ();
		void update ();
		Event<> &onRun ();
		int frameInterval;
	private:
		int _current;
		Event<> _onRun;
	};
}

#endif
