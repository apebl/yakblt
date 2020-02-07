#include "scheduler.hpp"

namespace yakblt {
	Scheduler::Scheduler (int frameInterval) :
			frameInterval(frameInterval),
			_current(0),
			_onRun()
	{
	}

	void Scheduler::reset () {
		_current = 0;
	}

	void Scheduler::update () {
		_current++;
		if (_current > frameInterval) {
			_onRun.fireEvent();
			_current = 0;
		}
	}

	Event<> &Scheduler::onRun () {
		return _onRun;
	}
}
